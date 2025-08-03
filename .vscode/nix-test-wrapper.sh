#!/usr/bin/env bash
# Wrapper script to run tests in Nix environment for VS Code Test Explorer

cd "$(dirname "$0")/.."
exec nix develop --command "${@}"
