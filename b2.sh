 #!/bin/bash

util/docker_build.sh sofle_pico:uberrice:uf2-split-left
mv sofle_pico_uberrice.uf2 uleft.uf2
util/docker_build.sh sofle_pico:uberrice:uf2-split-right
mv sofle_pico_uberrice.uf2 uright.uf2
