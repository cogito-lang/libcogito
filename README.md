# Cogito

[![Build Status](https://travis-ci.com/localytics/cogito-c.svg?token=kQUiABmGkzyHdJdMnCnv&branch=master)](https://travis-ci.com/localytics/cogito-c)

Cogito allows you to define your AWS IAM policies using a smaller, easier-to-read format. By writing:

```sql
allow dynamodb:Batch*, dynamodb:DeleteItem on dynamodb:::table/push*;
allow s3:PutRecord on kinesis:::stream/push*;
```

cogito will generate:

```json
[
  {
    "Effect": "Allow",
    "Action": [
      "dynamodb:Batch*",
      "dynamodb:DeleteItem"
    ],
    "Resource": [
      "arn:aws:dynamodb:::table/push*"
    ]
  },
  {
    "Effect": "Allow",
    "Action": [
      "s3:PutRecord"
    ],
    "Resource": [
      "arn:aws:kinesis:::stream/push*"
    ]
  }
]
```

## Getting Started

To get started, run:

```
autoreconf -i
./configure
make
make install
```

## Binary usage

You can convert between JSON and Cogito syntax on the command line:

```bash
$ cogito to-json 'ALLOW ec2:DescribeInstances ON *;'
[
  {
    "Effect": "Allow",
    "Action": [
      "ec2:DescribeInstances"
    ],
    "Resource": [
      "*"
    ]
  }
]

$ cogito to-iam '[{ "Effect": "Allow", "Action": "ec2:DescribeInstances", "Resource": "*" }]'
ALLOW
  ec2:DescribeInstances
ON
  *;
```

## Library usage

You can link again `libcogito` after it has been installed by including <cogito.h> in your C program. This will give you the functions `cg_to_json` and `cg_to_iam` which will return pointers to `response_t` structs. The structs have status and message fields that are integers and char*s respectively. If the status is 0 then the conversion succeeded and the message is the converted text. If the status is 1 then the conversion failed and the message is the error message.

## Dependencies

This program depends on [GNU Bison](https://www.gnu.org/software/bison/) and [flex](http://flex.sourceforge.net/). On Mac OSX you can install them using [homebrew](http://brew.sh/) like so:

    $ brew install flex bison

You may need to link them manually depending on your configuration, which you can do with:

    $ brew link flex --force
