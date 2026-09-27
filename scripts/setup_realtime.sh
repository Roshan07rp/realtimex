#!/bin/bash
set -e
sudo apt update
sudo apt install -y build-essential cmake git stress-ng
echo "Build and stress-test dependencies installed."
echo "Install/select a PREEMPT_RT kernel separately when required for your Ubuntu version."
