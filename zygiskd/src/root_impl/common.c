#include <sys/types.h>

#include "common.h"

#include "../utils.h"
#include "apatch.h"

static struct root_impl impl;

void root_impls_setup(void) {
  struct root_impl_state state_apatch;
  apatch_get_existence(&state_apatch);

  if (state_apatch.state == Supported) {
    impl.impl = APatch;
  } else {
    impl.impl = None;
  }

  switch (impl.impl) {
    case None: {
      LOGI("No root implementation found.\n");

      break;
    }
    case APatch: {
      LOGI("APatch root implementation found.\n");

      break;
    }
  }
}

void get_impl(struct root_impl *uimpl) {
  *uimpl = impl;
}

bool uid_granted_root(uid_t uid) {
  switch (impl.impl) {
    case APatch: {
      return apatch_uid_granted_root(uid);
    }
    default: {
      return false;
    }
  }
}

bool uid_should_umount(uid_t uid, const char *const process) {
  switch (impl.impl) {
    case APatch: {
      return apatch_uid_should_umount(uid, process);
    }
    default: {
      return false;
    }
  }
}

bool uid_is_manager(uid_t uid) {
  switch (impl.impl) {
    case APatch: {
      return apatch_uid_is_manager(uid);
    }
    default: {
      return false;
    }
  }
}

void root_impl_cleanup(void) {
  /* No cleanup needed for APatch */
}
