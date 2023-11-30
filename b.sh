#!/bin/bash

util/docker_build.sh sofle_pico:default:uf2-split-left
mv sofle_pico_rev1_default.uf2 left.uf2
util/docker_build.sh sofle_pico:default:uf2-split-right
mv sofle_pico_rev1_default.uf2 right.uf2
