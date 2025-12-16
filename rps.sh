#!/bin/bash

gcc $(pkg-config --cflags gtk+-3.0) \
    auth.c game.c stats.c variable.c ui.c main.c \
    -o main \
    $(pkg-config --libs gtk+-3.0)
