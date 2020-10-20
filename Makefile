.PHONY: clean All

All:
	@echo "----------Building project:[ libSCIDK - Debug ]----------"
	@cd "libSCIDK" && "$(MAKE)" -f  "libSCIDK-lib.mk"
	@echo "----------Building project:[ SciDKSDK_test - Debug ]----------"
	@cd "SciDKSDK_test" && "$(MAKE)" -f  "SciDKSDK_test-app.mk"
	@mkdir -p linux
	@cp libSCIDK/Debug/libSCIDK.so linux/.	
	@cp SciDKSDK_test/Debug/SciDKSDK_test linux/.	
	

clean:
	@echo "----------Cleaning project:[ libSCIDK - Debug ]----------"
	@cd "libSCIDK" && "$(MAKE)" -f  "libSCIDK.mk" clean
	@echo "----------Cleaning project:[ SciDKSDK_test - Debug ]----------"
	@cd "SciDKSDK_test" && "$(MAKE)" -f  "SciDKSDK_test-app.mk" clean
	@rm -rf linux

install:
	@cp linux/libSCIDK.so /usr/local/lib/libSCIDK.so
	@ldconfig
