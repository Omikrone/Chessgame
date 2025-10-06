FROM debian:12 AS build

RUN apt-get update && apt-get install -y \
    git \
    cmake \
    g++ \
    libboost-all-dev \
    libasio-dev \
    zlib1g-dev \
    && rm -rf /var/lib/apt/lists/*

RUN git clone https://github.com/Omikrone/Euphron.git /src

WORKDIR /src
RUN cmake -B build -S . -DCMAKE_BUILD_TYPE=Release && cmake --build build -j$(nproc)

RUN ls -l build/


FROM debian:12

COPY --from=build /src/build/src/engine/chessengine /usr/local/bin/chessengine
EXPOSE 18088
ENTRYPOINT ["/usr/local/bin/chessengine"]