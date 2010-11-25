%define name		fcitx
%define version		4.0.0
%define release		1

%define prefix		/usr
%define fcitxbindir	/usr/bin

Name:		%{name}
Version:	%{version}
Release:	%{release}
Summary:	Free Chinese Input Toy for X (XIM)
Packager:	Xie Yanbo <xyb76@sina.com>
URL:		http://www.fcitx.org/
Group:		System Environment/Libraries
Group(zh_CN):	用户界面/桌面
License:	GPL
Source:		%{name}-%{version}.tar.gz
BuildRequires:	cairo-devel
BuildRequires:  pango-devel
%if 0%{?suse_version}
BuildRequires:	dbus-1-devel
%else
BuildRequires:	dbus-devel
%endif
BuildRequires:	intltool
BuildRequires:	libtool
BuildRoot:	%{_tmppath}/%{name}-%{version}-%{release}

%description
FCITX is a simplified Chinese input server. It supports Tables,
Pinyin and QuWei input method. It's small and fast.

%description -l zh_CN
Fcitx──小企鹅输入法即Free Chinese Input Toy for X，它是一个以GPL方式
发布的、基于XIM的简体中文输入法(即原来的G五笔)，包括码表、全拼拼音、双拼
拼音输入法,并可运行在Linux及其它类UNIX平台上。
Designed by Yuking <yuking_net@suho.com>

%package devel
Summary:        Development files for %{name}
Group:          Development/Libraries
%if 0%{?suse_version}
Requires:   xorg-x11-libX11-devel
%else
Requires:   libX11-devel
%endif

%description devel
The %{name}-devel package includes the header files for the FCITX package.

%prep
%setup -q

%build
%configure \
    --enable-dbus \
    --enable-tray
make

%install
rm -rf $RPM_BUILD_ROOT

make DESTDIR=$RPM_BUILD_ROOT install-strip

rm -f $RPM_BUILD_ROOT%{_libdir}/libfcitx-config.la

%find_lang %{name}

%clean
[ ${RPM_BUILD_ROOT} != "/" ] && rm -rf ${RPM_BUILD_ROOT}

%files -f %{name}.lang
%defattr(-,root,root,-)
%doc AUTHORS ChangeLog COPYING INSTALL README
%doc doc/*.txt doc/*.htm
%{_bindir}/*
%{_datadir}/fcitx/
%{_datadir}/fcitx/*
%{_datadir}/pixmaps/*
%{_libdir}/libfcitx*

%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig

%files devel
%defattr(-,root,root,-)
%{_libdir}/pkgconfig/*.pc
%{_includedir}/*

%changelog
* Sat Sep 18 2010 CSSlayer <wengxt@gmail.com>
- Make it works with newest

* Fri Jun 11 2004 xyb <xyb76@sina.com>
- Add data/tables.conf

* Mon Feb 2 2004 xyb <xyb76@sina.com>
- Fix spec bug(patch by hamigua <hamigua@linuxsir.org>).

* Thu Jan 15 2004 xyb <xyb76@sina.com>
- skeleton RPM