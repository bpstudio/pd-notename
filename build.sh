#!/usr/bin/env bash
# Build notename Pd external (macOS default: notename.pd_darwin in this directory).
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$ROOT"

echo "Building in: $ROOT"
if [[ -n "${PDDIR:-}" ]]; then
  echo "Using PDDIR=$PDDIR"
  make PDDIR="$PDDIR" "$@"
else
  make "$@"
fi

echo "Done. Output: $(ls -1 "$ROOT"/notename.pd_darwin 2>/dev/null || true)"
