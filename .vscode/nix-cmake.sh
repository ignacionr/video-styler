#!/usr/bin/env bash
# Script to run CMake commands in the Nix environment

cd "$(dirname "$0")/.."
exec nix develop --command "$@"
