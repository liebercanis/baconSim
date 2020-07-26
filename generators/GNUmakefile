# GNUmakefile 
# Created for MaGe modules by Jason Detwiler, June 2005

include ../buildTools/config.mk

name := $(notdir $(shell pwd))
G4TARGET := $(name)
G4EXLIB := true

.PHONY: all
all: lib 

include /home/admin/geant4.10.04/config/binmake.gmk
include ../buildTools/install.mk
