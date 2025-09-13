FROM ubuntu:22.04


# Install dependencies & download and install Crow
RUN apt-get update && apt-get install -y libasio-dev curl wget cmake g++ make \
    && curl -L -o Crow.deb https://github.com/CrowCpp/Crow/releases/download/v1.2.1.2/Crow-1.2.1-Linux.deb \
    && apt install -y ./Crow.deb \
    && rm Crow.deb

# Copy the project
WORKDIR /app
COPY . /app

# Build the project
RUN cmake -B build -S . && cmake --build build

# Launch the server
CMD [ "./build/chess" ]
