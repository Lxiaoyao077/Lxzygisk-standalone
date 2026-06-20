#!/system/bin/sh

set -e

DEBUG=@DEBUG@

MODDIR=${0%/*}

if [ "$ZYGISK_ENABLED" ]; then
  sed -i "s|^description=|description=[❌ Disable Zygisk] |" "$MODDIR/module.prop"

  exit 0
fi

cd "$MODDIR"

exit 0
