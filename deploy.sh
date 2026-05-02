#!/usr/bin/env bash
# Install notename into the Pd user externals tree.
# Default PDLIBDIR: ~/Documents/pd/externals -> creates:
#   ~/Documents/pd/externals/notename/notename.pd_darwin
#   ~/Documents/pd/externals/notename/notename-help.pd
# Override: PDLIBDIR=/other/parent ./deploy.sh
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$ROOT"

PDLIBDIR="${PDLIBDIR:-$HOME/Documents/pd/externals}"

echo "Deploy target: $PDLIBDIR/notename/"
if [[ -n "${PDDIR:-}" ]]; then
  echo "Using PDDIR=$PDDIR"
  make install PDLIBDIR="$PDLIBDIR" PDDIR="$PDDIR"
else
  make install PDLIBDIR="$PDLIBDIR"
fi

echo "Add this path in Pd (Preferences -> Path): $PDLIBDIR"
echo "(Pd loads [notename] from the notename/ folder under that path.)"
