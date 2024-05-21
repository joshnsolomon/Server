# syntax=docker/dockerfile:1

FROM gcc:latest
COPY . .
RUN chmod +x ./run.sh
RUN ./run.sh
EXPOSE 8080
CMD ["./server"]