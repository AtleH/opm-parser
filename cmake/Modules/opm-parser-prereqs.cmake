# -*- mode: cmake; tab-width: 2; indent-tabs-mode: t; truncate-lines: t; compile-command: "cmake -Wdev" -*-
# vim: set filetype=cmake autoindent tabstop=2 shiftwidth=2 noexpandtab softtabstop=2 nowrap:

# defines that must be present in config.h for our headers
set (opm-parser_CONFIG_VAR
	HAVE_ERT
	)

# dependencies
set (opm-parser_DEPS
	# compile with C99 support if available
	"C99"
	# compile with C++0x/11 support if available
	"CXX11Features REQUIRED"
	# various runtime library enhancements
	"Boost 1.44.0
		COMPONENTS date_time filesystem system iostream unit_test_framework REQUIRED"
	"cJSON"
	# Ensembles-based Reservoir Tools (ERT)
	"ERT REQUIRED"
	)
