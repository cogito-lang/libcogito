# libcogito

[![Build Status](https://travis-ci.com/localytics/libcogito.svg?token=kQUiABmGkzyHdJdMnCnv&branch=master)](https://travis-ci.com/localytics/libcogito)

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

You can link against `libcogito` after it has been installed by including `cogito.h` in your C program. This will give you a `buffer` struct:

```c
typedef struct cg_buf {
  size_t length;
  size_t capacity;
  char *content;
} cg_buf_t;
```

and two functions: `cg_to_json` and `cg_to_iam`. The call signature for these functions is:

```c
int cg_to_json(cg_buf_t *buffer, char *input);
int cg_to_iam(cg_buf_t *buffer, char *input);
```

where the return value will be a 0 in the case of success and an error code otherwise.

## Dependencies

You need to install autoconf and automake for the `autoreconf -i` command to
work, like so:

    $ brew install autoconf automake

This program depends on [GNU Bison](https://www.gnu.org/software/bison/) and [flex](http://flex.sourceforge.net/). On Mac OSX you can install them using [homebrew](http://brew.sh/) like so:

    $ brew install flex bison

You may need to link them manually depending on your configuration, which you can do with:

    $ brew link flex --force

## Testing

In order to work with the tests, ensure you have `check` installed on your system:

    $ brew install check

Now you can run:

    $ make check

to run the unit tests. In order to run the integration tests, run:

    $ tests/integration/test

## Building

To build the necessary artifacts, make sure docker is running on your machine. Then, to build the debian package, run:

    $ docker build -t libcogito:debian debian
    $ docker run -it -v $(pwd):/data libcogito:debian

And to build the Amazon Linux package, run:

    $ autoreconf -i
    $ ./configure
    $ docker build -t libcogito:amazon amazon
    $ docker run -it -v $(pwd):/data libcogito:amazon

## Credits

The [CCAN](https://ccodearchive.net/) JSON library is used by libcogito uses for parsing and generating JSON.
