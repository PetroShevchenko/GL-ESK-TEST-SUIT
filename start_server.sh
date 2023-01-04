#!/bin/sh

PORT=5678

cd ./utils
echo "Launching UDP server..."
echo "Press 'exit' to exit"
./udp_server ${PORT}

