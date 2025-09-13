# Use Ubuntu 22.04 as base image
FROM ubuntu:22.04

# ----------------------------
# Install build dependencies
# ----------------------------
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    g++ \
    make \
    pkg-config \
    libasio-dev \
    zlib1g-dev \
    libssl-dev \
    libboost-system-dev \
    libboost-filesystem-dev \
    libboost-thread-dev \
    curl \
    wget \
    dpkg \
    && rm -rf /var/lib/apt/lists/*

# Download and install Crow
RUN curl -L -o Crow.deb https://github.com/CrowCpp/Crow/releases/download/v1.2.1.2/Crow-1.2.1-Linux.deb \
    && apt install -y ./Crow.deb \
    && rm Crow.deb

# ----------------------------
# Copy project files into the container
# ----------------------------
WORKDIR /app
COPY . /app

# ----------------------------
# Build the project
# ----------------------------
RUN cmake -B build -S . \
    && cmake --build build --config Release

# ----------------------------
# Launch the server when the container starts
# ----------------------------
CMD ["./build/chess"]
