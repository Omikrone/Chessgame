FROM ubuntu:22.04

# Install dependencies
RUN apt-get update && apt-get install -y \
    cmake g++ make curl wget dpkg \
    && rm -rf /var/lib/apt/lists/*

# Download and install Crow
RUN curl -L -o Crow.deb https://github.com/CrowCpp/Crow/releases/download/v1.2.1.2/Crow-1.2.1-Linux.deb \
    && dpkg -i Crow.deb \
    && rm Crow.deb

# Copy the project
WORKDIR /app
COPY . /app

# Build the project
RUN cmake -B build -S . && cmake --build build

# Launch the server
CMD [ "./build/chess" ]
