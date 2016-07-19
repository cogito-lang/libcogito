# Cogito

[![Build Status](https://travis-ci.com/localytics/cogito-c.svg?token=kQUiABmGkzyHdJdMnCnv&branch=master)](https://travis-ci.com/localytics/cogito-c)

Cogito allows you to define your AWS IAM policies using a smaller, easier-to-read format. Instead of:

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

you can define that by writing:

```sql
allow dynamodb:Batch*, dynamodb:DeleteItem on dynamodb:::table/push*;
allow s3:PutRecord on kinesis:::stream/push*;
```

## Dependencies

This program depends on [GNU Bison](https://www.gnu.org/software/bison/), [flex](http://flex.sourceforge.net/), and [json-c](https://github.com/json-c/json-c). On Mac OSX you can install them using [homebrew](http://brew.sh/) like so:

    $ brew install flex bison json-c

You may need to link them manually depending on your configuration, which you can do with:

    $ brew link flex --force
