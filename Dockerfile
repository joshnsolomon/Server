# syntax=docker/dockerfile:1

FROM node:18-alpine
RUN apk add build-base
COPY . .
RUN chmod +x ./run.sh
RUN ./run.sh
EXPOSE 80
ENTRYPOINT ["./server"]