FROM ubuntu:latest

RUN apt-get update && apt-get install -y \
    g++ \
    make

WORKDIR /app
COPY . /app
RUN g++ -c fonts/util.cc fonts/util.h
RUN g++ -c fonts/registro.cc fonts/registro.h
RUN  g++ -c fonts/arquivohash.cc fonts/arquivohash.h

RUN g++ -o upload fonts/upload.cc arquivohash.o util.o registro.o
RUN g++ -o findrec fonts/findrec.cc arquivohash.o util.o registro.o
