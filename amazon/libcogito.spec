Name:     libcogito
Version:  0.2.0
Release:  1
Summary:  Define your AWS IAM policies using an easy-to-read format.
License:  MIT
URL:      https://github.com/localytics/libcogito
Source0:  %{name}-%{version}.tar.gz

%description
Define your AWS IAM policies using an easy-to-read format.

%changelog
* Fri Jun 02 2017 Localytics <oss@localytics.com> - 0.2.0-1
- Allow "NotAction" and "NotResource" keys.

* Mon May 15 2017 Localytics <oss@localytics.com> - 0.1.1-1
- Fix issue when the "Action" or "Resource" keys are not provided.

* Fri Sep 02 2016 Localytics <oss@localytics.com> - 0.0.1-1
- Initial release
