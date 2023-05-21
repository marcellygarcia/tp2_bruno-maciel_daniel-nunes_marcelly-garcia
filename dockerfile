FROM ubuntu:latest

RUN apt-get update && apt-get install -y \
    g++ \
    make

WORKDIR /app
COPY . /app
RUN g++ -c fonts/util.cc fonts/util.h
RUN g++ -c fonts/registro.cc fonts/registro.h
RUN g++ -c fonts/arquivoHash.cc fonts/arquivoHash.h

RUN g++ -o upload fonts/upload.cc
RUN g++ -o findrec fonts/findrec.cc
