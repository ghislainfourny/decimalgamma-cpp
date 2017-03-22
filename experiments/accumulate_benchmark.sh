#!/bin/bash

SCRIPTNAME="$(realpath $0 | xargs basename)"
PROJECTROOT="$(realpath $0 | xargs dirname | xargs dirname)"

if [[ -z "$PROJECTROOT" ]]; then exit 1; fi

"${PROJECTROOT}/gen/accumulate_bench" | \
    "${PROJECTROOT}/scripts/jsonlines2csv.py" > \
    "${PROJECTROOT}/experiments/output/${SCRIPTNAME%sh}csv"
