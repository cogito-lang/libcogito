Name:     libcogito
Version:  0.2.0
Release:  1
Summary:  Define your AWS IAM policies using an easy-to-read format.
License:  MIT
URL:      https://github.com/cogito-lang/libcogito
Source0:  %{name}-%{version}.tar.gz

%description
Define your AWS IAM policies using an easy-to-read format.

%changelog
* Fri Jun 02 2017 Kevin Deisz <kevin.deisz@gmail.com> - 0.2.0-1
- Allow "NotAction" and "NotResource" keys.

* Mon May 15 2017 Kevin Deisz <kevin.deisz@gmail.com> - 0.1.1-1
- Fix issue when the "Action" or "Resource" keys are not provided.

* Fri Sep 02 2016 Kevin Deisz <kevin.deisz@gmail.com> - 0.0.1-1
- Initial release
