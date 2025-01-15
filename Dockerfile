FROM alpine:latest
WORKDIR /grafo-cpp
RUN apk add --no-cache --update build-base cmake
COPY ./ ./
RUN ./build
CMD ["./_build/grafo-cpp"]
