#!/bin/sh
# Fetch local-only decomp tools not tracked in git:
#   - m2c at the commit pinned by the tools/m2c_repo gitlink
#   - objdiff-cli with `diff --format json` (needed by tools/feedback_diff.py),
#     installed into .venv/bin/objdiff
set -e
cd "$(dirname "$0")/.."
M2C_COMMIT=400dd3471df589a6fc7af983921f43a4cf9af473
OBJDIFF_VERSION=v3.8.2

if [ ! -f tools/m2c_repo/m2c.py ]; then
    rm -rf tools/m2c_repo
    git clone -q https://github.com/matt-kempster/m2c.git tools/m2c_repo
    git -C tools/m2c_repo checkout -q "$M2C_COMMIT"
fi

if [ ! -x .venv/bin/objdiff ]; then
    curl -sSfL -o .venv/bin/objdiff \
        "https://github.com/encounter/objdiff/releases/download/$OBJDIFF_VERSION/objdiff-cli-linux-x86_64"
    chmod +x .venv/bin/objdiff
fi

.venv/bin/python -m pip install -q -r requirements-dev.txt
echo "Dev tools ready."
