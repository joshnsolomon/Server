#!/bin/sh

docker build -t server .
docker run -p 127.0.0.1:8080:8080 server
