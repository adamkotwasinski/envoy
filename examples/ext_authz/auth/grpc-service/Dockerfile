FROM golang:1.20.4-bullseye@sha256:d282e704848c81e313b17c68e27edd44202937db196398915077830557f82588 as builder

COPY . /app
RUN make -C /app/grpc-service

FROM debian:bullseye-slim

COPY --from=builder /app/grpc-service/server /app/server
CMD ["/app/server", "-users", "/etc/users.json"]
