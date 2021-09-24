#
# Copyright (C) 2006-2021 OpenWrt.org
# Copyright (C) 2021 Nicolas Thill <nicolas.thill@gmail.com>
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=tw-c-sdk
PKG_VERSION:=2.2.12.1052
PKG_RELEASE:=1

PKG_SOURCE:=C-SDK-$(subst .,-,$(PKG_VERSION)).zip
PKG_SOURCE_URL:=https://tpg-twxdevzone.s3.amazonaws.com/files/media/brewmaster/trialeditions/downloads/9_1/sdk/
PKG_HASH:=9ff8321758d38258d594ad4db613aad2bcce340723457fd94140d5ea3a4a12a8

PKG_BUILD_DIR:=$(BUILD_DIR)/c-sdk-$(PKG_VERSION)-development

#PKG_LICENSE:=?
#PKG_LICENSE_FILES:=

PKG_MAINTAINER:=Nicolas Thill <nicolas.thill@gmail.com>

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/cmake.mk

CMAKE_OPTIONS += -DTHINGWORX_CSDK_OPENSSL_BIN_DIR=$(STAGING_DIR)/usr/bin
CMAKE_OPTIONS += -DTHINGWORX_CSDK_OPENSSL_INCLUDE_DIR=$(STAGING_DIR)/usr/include
CMAKE_OPTIONS += -DTHINGWORX_CSDK_OPENSSL_LIB_DIR=$(STAGING_DIR)/usr/lib

define Package/tw-c-sdk
  SECTION:=libs
  CATEGORY:=Libraries
  TITLE:=ThingWorx C SDK
  URL:=https://developer.thingworx.com/en/sdks
  DEPENDS:=+libopenssl
endef

define Build/InstallDev
	$(INSTALL_DIR) $(1)/usr/include
	$(CP) $(PKG_INSTALL_DIR)/usr/include/thingworx $(1)/usr/include/
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/libtw*.so* $(1)/usr/lib/
endef

define Package/tw-c-sdk/install
	$(INSTALL_DIR) $(1)/usr/include
	$(CP) $(PKG_INSTALL_DIR)/usr/include/thingworx $(1)/usr/include/
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/libtw*.so.* $(1)/usr/lib/
endef

$(eval $(call BuildPackage,tw-c-sdk))
