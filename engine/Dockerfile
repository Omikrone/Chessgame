FROM debian:12 AS build

RUN apt-get update && apt-get install -y git cmake g++

RUN git clone https://github.com/Omikrone/Euphron.git /src

WORKDIR /src
RUN cmake -B build -S . && cmake --build build --config Release


FROM debian:12

COPY --from=build /src/build/chessengine /usr/local/bin/chessengine
EXPOSE 18088
ENTRYPOINT ["/usr/local/bin/chessengine"]
