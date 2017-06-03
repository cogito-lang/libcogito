# libcogito

[![Build Status](https://travis-ci.org/localytics/libcogito.svg?branch=master)](https://travis-ci.org/localytics/libcogito)

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

## Installation

To get started on Mac, we host Cogito as a [homebrew formula](https://github.com/localytics/homebrew-formulae), so to install run:
 
```sh
brew tap localytics/formulae
brew install cogito
```
 
On other debian-based systems, you can install it with:
 
```sh
FILE=$(mktemp)
wget 'https://s3.amazonaws.com/public.localytics/artifacts/libcogito_0.2.0-1_amd64.deb' -qO $FILE
sudo dpkg -i $FILE && rm $FILE
```
 
On amazon linux, you can download the appropriate object file from our S3 bucket here:
 
```sh
wget https://s3.amazonaws.com/public.localytics/artifacts/cogito/amazon/libcogito.so
```

To install from source, checkout this repository and run:

```sh
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
typedef struct {
  size_t length;
  size_t capacity;
  char *content;
} cg_buf_t;
```

and two functions: `cg_to_json` and `cg_to_iam`. The call signature for these functions is:

```c
int cg_to_json(cg_buf_t *buffer, char *str);
int cg_to_iam(cg_buf_t *buffer, char *str);
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

To build the necessary artifacts, make sure `docker` is running on your machine. Then, ensure that you've built the necessary autotools files with `autoreconf -i` and `./configure`. Then, to build the debian package, run:

    $ make debian-build

And to build the Amazon Linux package, run:

    $ make amazon-build

## Releasing

Releasing a new version requires updating things in a couple places - follow the below script:

- Update the [amazon rpm spec](amazon/libcogito.spec) and the [debian changelog](debian/changelog).
- Merge the changes into master.
- Tag a release off of master with the new version and update the GitHub release docs.
- Build the packages artifacts (see Building above).
- Upload the artifacts to S3 under the `public.localytics` bucket.
- Update the [homebrew formula](https://github.com/localytics/homebrew-formulae/blob/master/Formula/cogito.rb) to point to the latest version.

## Credits

The [CCAN](https://ccodearchive.net/) JSON library is used by libcogito uses for parsing and generating JSON.
