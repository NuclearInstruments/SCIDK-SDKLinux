##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=libSCIDK
ConfigurationName      :=Debug
WorkspacePath          :=/home/user/Documents/SCIDK
ProjectPath            :=/home/user/Documents/SCIDK/libSCIDK
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=user
Date                   :=20/10/20
CodeLitePath           :=/home/user/.codelite
LinkerName             :=/usr/bin/g++
SharedObjectLinkerName :=/usr/bin/g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/$(ProjectName).so
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="libSCIDK.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := $(LibrarySwitch)ftd2xx 
ArLibs                 :=  "ftd2xx" 
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := /usr/bin/ar rcu
CXX      := /usr/bin/g++
CC       := /usr/bin/gcc
CXXFLAGS :=  -g -fPIC $(Preprocessors)
CFLAGS   :=  -g -fPIC $(Preprocessors)
ASFLAGS  := 
AS       := /usr/bin/as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/src_FTDI_CPP_DLL.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_SCIDK_API_C.cpp$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(SharedObjectLinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)
	@$(MakeDirCommand) "/home/user/Documents/SCIDK/.build-debug"
	@echo rebuilt > "/home/user/Documents/SCIDK/.build-debug/libSCIDK"

MakeIntermediateDirs:
	@test -d ./Debug || $(MakeDirCommand) ./Debug


$(IntermediateDirectory)/.d:
	@test -d ./Debug || $(MakeDirCommand) ./Debug

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/src_FTDI_CPP_DLL.cpp$(ObjectSuffix): src/FTDI_CPP_DLL.cpp $(IntermediateDirectory)/src_FTDI_CPP_DLL.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/user/Documents/SCIDK/libSCIDK/src/FTDI_CPP_DLL.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_FTDI_CPP_DLL.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_FTDI_CPP_DLL.cpp$(DependSuffix): src/FTDI_CPP_DLL.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_FTDI_CPP_DLL.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_FTDI_CPP_DLL.cpp$(DependSuffix) -MM src/FTDI_CPP_DLL.cpp

$(IntermediateDirectory)/src_FTDI_CPP_DLL.cpp$(PreprocessSuffix): src/FTDI_CPP_DLL.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_FTDI_CPP_DLL.cpp$(PreprocessSuffix) src/FTDI_CPP_DLL.cpp

$(IntermediateDirectory)/src_SCIDK_API_C.cpp$(ObjectSuffix): src/SCIDK_API_C.cpp $(IntermediateDirectory)/src_SCIDK_API_C.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/user/Documents/SCIDK/libSCIDK/src/SCIDK_API_C.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_SCIDK_API_C.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_SCIDK_API_C.cpp$(DependSuffix): src/SCIDK_API_C.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_SCIDK_API_C.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_SCIDK_API_C.cpp$(DependSuffix) -MM src/SCIDK_API_C.cpp

$(IntermediateDirectory)/src_SCIDK_API_C.cpp$(PreprocessSuffix): src/SCIDK_API_C.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_SCIDK_API_C.cpp$(PreprocessSuffix) src/SCIDK_API_C.cpp


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


