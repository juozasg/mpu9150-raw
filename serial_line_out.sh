#!/bin/bash

DEV=${1:-/dev/ttyACM0}
BR=${2:-115200}

OUT="$HOME/serial-line.out"
LOG="$HOME/serial-line.log"

echo $DEV to $OUT and $LOG at $BR
rm "$LOG"
socat FILE:$DEV,b$BR,raw,rdonly - | \
  xargs -d '\n' -I LN \
      sh -c "echo LN > $OUT; echo $(date +'%T.%3N') LN >> $LOG"