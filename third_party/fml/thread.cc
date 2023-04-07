// Copyright 2013 The Flutter Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#define FML_USED_ON_EMBEDDER

#include "fml/thread.h"

#include <memory>
#include <string>
#include <utility>

#include "fml/build_config.h"
#include "fml/message_loop.h"
#include "fml/synchronization/waitable_event.h"

#if defined(FML_OS_WIN)
#include <windows.h>
#elif defined(OS_FUCHSIA)
#include <lib/zx/thread.h>
#else
#include <pthread.h>
#endif

namespace fml {

#if defined(FML_OS_WIN)
// The information on how to set the thread name comes from
// a MSDN article: http://msdn2.microsoft.com/en-us/library/xcb2z8hs.aspx
const DWORD kVCThreadNameException = 0x406D1388;
typedef struct tagTHREADNAME_INFO {
  DWORD dwType;      // Must be 0x1000.
  LPCSTR szName;     // Pointer to name (in user addr space).
  DWORD dwThreadID;  // Thread ID (-1=caller thread).
  DWORD dwFlags;     // Reserved for future use, must be zero.
} THREADNAME_INFO;
#endif

void SetThreadName(const std::string& name) {
  if (name == "") {
    return;
  }
#if defined(FML_OS_MACOSX)
  pthread_setname_np(name.c_str());
#elif defined(FML_OS_LINUX) || defined(FML_OS_ANDROID)
  pthread_setname_np(pthread_self(), name.c_str());
#elif defined(FML_OS_WIN)
  THREADNAME_INFO info;
  info.dwType = 0x1000;
  info.szName = name.c_str();
  info.dwThreadID = GetCurrentThreadId();
  info.dwFlags = 0;
  __try {
    RaiseException(kVCThreadNameException, 0, sizeof(info) / sizeof(DWORD),
                   reinterpret_cast<DWORD_PTR*>(&info));
  } __except (EXCEPTION_CONTINUE_EXECUTION) {
  }
#elif defined(OS_FUCHSIA)
  zx::thread::self()->set_property(ZX_PROP_NAME, name.c_str(), name.size());
#else
  FML_DLOG(INFO) << "Could not set the thread name to '" << name
                 << "' on this platform.";
#endif
}

void Thread::SetCurrentThreadName(const Thread::ThreadConfig& config) {
  SetThreadName(config.name);
}

Thread::Thread(const std::string& name)
    : Thread(Thread::SetCurrentThreadName, ThreadConfig(name)) {}

Thread::Thread(const ThreadConfigSetter& setter, const ThreadConfig& config)
    : joined_(false) {
  fml::AutoResetWaitableEvent latch;
  fml::RefPtr<fml::TaskRunner> runner;

  thread_ = std::make_unique<std::thread>(
      [&latch, &runner, setter, config]() -> void {
        setter(config);
        fml::MessageLoop::EnsureInitializedForCurrentThread();
        auto& loop = MessageLoop::GetCurrent();
        runner = loop.GetTaskRunner();
        latch.Signal();
        loop.Run();
      });
  latch.Wait();
  task_runner_ = runner;
}

Thread::~Thread() {
  Join();
}

fml::RefPtr<fml::TaskRunner> Thread::GetTaskRunner() const {
  return task_runner_;
}

void Thread::Join() {
  if (joined_) {
    return;
  }
  joined_ = true;
  task_runner_->PostTask([]() { MessageLoop::GetCurrent().Terminate(); });
  thread_->join();
}

}  // namespace fml
