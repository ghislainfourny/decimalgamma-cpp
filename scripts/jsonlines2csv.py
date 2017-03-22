#!/usr/bin/env python3

import sys, json

keys = set()
records = []
num_empty_records = 0

for line in sys.stdin:
    record = json.loads(line)
    if len(record) == 0:
        num_empty_records += 1
        continue
    records.append(record)
    keys.update(record.keys())

print(";".join(keys))

for record in records:
    print(";".join([str(record.get(key,"")) for key in keys]))

if num_empty_records > 0:
    sys.stderr.write("Warning: {0} empty records found!\n".format(num_empty_records))
