FROM debian:12 AS build

RUN apt-get update && apt-get install -y libssl3 cmake g++ git cmake g++ git libboost-all-dev zlib1g-dev libssl-dev libasio-dev zlib1g-dev \
        && rm -rf /var/lib/apt/lists/*

WORKDIR /app
COPY . .
RUN cmake -B build -S . && cmake --build build --config Release


FROM debian:12

RUN apt-get update && apt-get install -y libssl3

WORKDIR /app

COPY --from=build /app/build/chessgame /usr/local/bin/chessgame

EXPOSE 18080
ENTRYPOINT ["/usr/local/bin/chessgame"]
