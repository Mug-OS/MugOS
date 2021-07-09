################################################################
#                                                              #
#         This make file will get TinyCC from internet         #
#                And build it locally in a dir                 #
#             So it can be used to build the MugOS             #
#                                                              #
################################################################

# Main variables

mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
current_dir := $(dir $(mkfile_path))
WGETPARAMETERS = -O

OUTPUTFOLDER = bin
TEMPFOLDER = dump
TINYCCVERSION = 0.9.27
TEMPFOLDERPATH = ${current_dir}/${TEMPFOLDER}
FOLDERPATH = ${current_dir}/${OUTPUTFOLDER}
FINALTCCPATH = ${current_dir}/${OUTPUTFOLDER}/tcc
TINYCCDOWNLOADFOLDER = ${TEMPFOLDERPATH}/tcc-$(TINYCCVERSION).tar.bz2
TEMPUNCOMPRESSEDFOLDER = ${current_dir}/${OUTPUTFOLDER}/tcc-$(TINYCCVERSION)

TINYCCURL = "http://download.savannah.gnu.org/releases/tinycc/tcc-$(TINYCCVERSION).tar.bz2"

7ZIPCOMMAND = 7z

# Main execution properties
#	Check if 7zip exists
ifndef ($(7ZIPCOMMAND))
	ifneq ($(OS),Windows_NT)
@$(info 7zip not founded) \
@$(info ) \
@$(info in order to this makefile work it is needed) \
@$(info if you have it, make sure it is on your path) \
@$(info ) \
@$(info if you have other preference of decompressing tool you can download Tiny C Compiler from web and build it locally and ignore this folder) \
@$(info ) \
@$(error )
	endif
endif

#	Run only on windows
	ifeq ($(OS),Windows_NT)
#		Force run on powershell
		SHELL := powershell.exe
		.SHELLFLAGS := -NoProfile -Command

#		Change wget parameters
		WGETPARAMETERS = -outfile
#		Change mv command to move

#		Change file to download
		TINYCCURL = https://download.savannah.gnu.org/releases/tinycc/tcc-$(TINYCCVERSION)-win32-bin.zip
		TINYCCDOWNLOADFOLDER = ${TEMPFOLDERPATH}/tcc-$(TINYCCVERSION).zip
	endif

# SubFunctions functions
$(FINALTCCPATH): $(TEMPUNCOMPRESSEDFOLDER)
ifneq ($(OS),Windows_NT)
	@mv "${TEMPUNCOMPRESSEDFOLDER}" "${FINALTCCPATH}"
endif

$(TEMPFOLDERPATH):
	@mkdir "$(TEMPFOLDERPATH)"

$(FOLDERPATH):
	@mkdir "${current_dir}/${OUTPUTFOLDER}"

$(TINYCCDOWNLOADFOLDER): $(TEMPFOLDERPATH)
	@wget ${WGETPARAMETERS} "${TINYCCDOWNLOADFOLDER}" "${TINYCCURL}"

$(TEMPUNCOMPRESSEDFOLDER): $(TINYCCDOWNLOADFOLDER) $(FOLDERPATH)
ifeq ($(OS),Windows_NT)
	@&Expand-Archive "${TINYCCDOWNLOADFOLDER}" "${current_dir}/${OUTPUTFOLDER}"
else
	@${7ZIPCOMMAND} x "${TINYCCDOWNLOADFOLDER}" -o"${TEMPFOLDERPATH}" -aoa
	@${7ZIPCOMMAND} x "${TEMPFOLDERPATH}/tcc-$(TINYCCVERSION).tar" -o"${current_dir}/${OUTPUTFOLDER}" -aoa
endif

downloader: $(FINALTCCPATH)
	@$(info "TinyCC downloaded with sucess")

installertor: downloader
ifeq ($(OS),Windows_NT)
 	${info "Not implemented runner for "./installer.sh" run by your self, or wait to someone who have a linux implement it"}
endif
