#!/bin/sh

docker build -t gettin-started .
docker run -p 127.0.0.1:80:80 gettin-started
