#
# Copyright (C) 2006-2021 OpenWrt.org
# Copyright (C) 2021 Nicolas Thill <nicolas.thill@gmail.com>
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=tw-c-client-mini
PKG_VERSION:=0.1
PKG_RELEASE:=1

#PKG_SOURCE:=
#PKG_SOURCE_URL:=
#PKG_HASH:=

#PKG_LICENSE:=?
#PKG_LICENSE_FILES:=

PKG_MAINTAINER:=Nicolas Thill <nicolas.thill@gmail.com>

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/cmake.mk

define Package/tw-c-client-mini
  SECTION:=libs
  CATEGORY:=Libraries
  TITLE:=ThingWorx C SDK Minimal Client
  URL:=https://developer.thingworx.com/en/sdks
  DEPENDS:=+tw-c-sdk
endef

define Package/tw-c-client-mini/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(CP) $(PKG_INSTALL_DIR)/usr/bin/twCSdkClientMini $(1)/usr/bin/
endef

$(eval $(call BuildPackage,tw-c-client-mini))
