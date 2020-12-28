; Script generated by the HM NIS Edit Script Wizard.

; HM NIS Edit Wizard helper defines
!define PRODUCT_NAME "Bib2Book"
!define PRODUCT_VERSION "1.0"
!define PRODUCT_PUBLISHER "Hailin"
!define PRODUCT_WEB_SITE "https://hailin.blog"
!define PRODUCT_DIR_REGKEY "Software\Microsoft\Windows\CurrentVersion\App Paths\Bib2Book.exe"
!define PRODUCT_UNINST_KEY "Software\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT_NAME}"
!define PRODUCT_UNINST_ROOT_KEY "HKLM"

; MUI 1.67 compatible ------
!include "MUI.nsh"

; MUI Settings
!define MUI_ABORTWARNING
!define MUI_ICON "${NSISDIR}\Contrib\Graphics\Icons\modern-install.ico"
!define MUI_UNICON "${NSISDIR}\Contrib\Graphics\Icons\modern-uninstall.ico"

; Language Selection Dialog Settings
!define MUI_LANGDLL_REGISTRY_ROOT "${PRODUCT_UNINST_ROOT_KEY}"
!define MUI_LANGDLL_REGISTRY_KEY "${PRODUCT_UNINST_KEY}"
!define MUI_LANGDLL_REGISTRY_VALUENAME "NSIS:Language"

; Welcome page
!insertmacro MUI_PAGE_WELCOME
; License page
!insertmacro MUI_PAGE_LICENSE "LICENSE"
; Directory page
!insertmacro MUI_PAGE_DIRECTORY
; Instfiles page
!insertmacro MUI_PAGE_INSTFILES
; Finish page
!define MUI_FINISHPAGE_RUN "$INSTDIR\Bib2Book.exe"
!define MUI_FINISHPAGE_SHOWREADME "$INSTDIR\documentation\doc.pdf"
!insertmacro MUI_PAGE_FINISH

; Uninstaller pages
!insertmacro MUI_UNPAGE_INSTFILES

; Language files
!insertmacro MUI_LANGUAGE "English"
!insertmacro MUI_LANGUAGE "SimpChinese"

; MUI end ------

Name "${PRODUCT_NAME} ${PRODUCT_VERSION}"
OutFile "Bib2Book_Setup.exe"
InstallDir "$PROGRAMFILES\Bib2Book"
InstallDirRegKey HKLM "${PRODUCT_DIR_REGKEY}" ""
ShowInstDetails show
ShowUnInstDetails show

Function .onInit
  !insertmacro MUI_LANGDLL_DISPLAY
FunctionEnd

Section "MainSection" SEC01
  SetOutPath "$INSTDIR"
  SetOverwrite try
  File "release\Bib2Book.exe"
  CreateDirectory "$SMPROGRAMS\Bib2Book"
  CreateShortCut "$SMPROGRAMS\Bib2Book\Bib2Book.lnk" "$INSTDIR\Bib2Book.exe"
  CreateShortCut "$DESKTOP\Bib2Book.lnk" "$INSTDIR\Bib2Book.exe"
  File "release\Compile.bat"
  File "release\D3Dcompiler_47.dll"
  SetOutPath "$INSTDIR\documentation"
  File "release\documentation\doc.pdf"
  SetOutPath "$INSTDIR\fonts\cormorant-garamond"
  File "release\fonts\cormorant-garamond\CormorantGaramond-Bold.ttf"
  File "release\fonts\cormorant-garamond\CormorantGaramond-BoldItalic.ttf"
  File "release\fonts\cormorant-garamond\CormorantGaramond-Italic.ttf"
  File "release\fonts\cormorant-garamond\CormorantGaramond-Light.ttf"
  File "release\fonts\cormorant-garamond\CormorantGaramond-LightItalic.ttf"
  File "release\fonts\cormorant-garamond\CormorantGaramond-Medium.ttf"
  File "release\fonts\cormorant-garamond\CormorantGaramond-MediumItalic.ttf"
  File "release\fonts\cormorant-garamond\CormorantGaramond-Regular.ttf"
  File "release\fonts\cormorant-garamond\CormorantGaramond-SemiBold.ttf"
  File "release\fonts\cormorant-garamond\CormorantGaramond-SemiBoldItalic.ttf"
  File "release\fonts\cormorant-garamond\OFL.txt"
  SetOutPath "$INSTDIR\iconengines"
  File "release\iconengines\qsvgicon.dll"
  SetOutPath "$INSTDIR\imageformats"
  File "release\imageformats\qgif.dll"
  File "release\imageformats\qicns.dll"
  File "release\imageformats\qico.dll"
  File "release\imageformats\qjpeg.dll"
  File "release\imageformats\qsvg.dll"
  File "release\imageformats\qtga.dll"
  File "release\imageformats\qtiff.dll"
  File "release\imageformats\qwbmp.dll"
  File "release\imageformats\qwebp.dll"
  SetOutPath "$INSTDIR"
  File "release\Install-Fonts.bat"
  File "release\libEGL.dll"
  File "release\libgcc_s_seh-1.dll"
  File "release\libgcc_s_sjlj-1.dll"
  File "release\libGLESv2.dll"
  File "release\libstdc++-6.dll"
  File "release\libwinpthread-1.dll"
  File "release\opengl32sw.dll"
  File "release\libcrypto-1_1-x64.dll"
  File "release\libssl-1_1-x64.dll"
  SetOutPath "$INSTDIR\platforms"
  File "release\platforms\qwindows.dll"
  SetOutPath "$INSTDIR"
  File "release\Qt5Core.dll"
  File "release\Qt5Gui.dll"
  File "release\Qt5Svg.dll"
  File "release\Qt5Widgets.dll"
  SetOutPath "$INSTDIR\styles"
  File "release\styles\qwindowsvistastyle.dll"
  SetOutPath "$INSTDIR\stys"
  File "release\stys\aicescover.sty"
  SetOutPath "$INSTDIR\stys\aiceslogos"
  File "release\stys\aiceslogos\aices.eps"
  File "release\stys\aiceslogos\aices.pdf"
  File "release\stys\aiceslogos\rwth.eps"
  File "release\stys\aiceslogos\rwth.pdf"
  File "release\stys\aiceslogos\tongji.png"
  SetOutPath "$INSTDIR\translations"
  File "release\translations\Bib2Book_cn.qm"
  File "release\translations\Bib2Book_en.qm"
  File "release\translations\qt_ar.qm"
  File "release\translations\qt_bg.qm"
  File "release\translations\qt_ca.qm"
  File "release\translations\qt_cs.qm"
  File "release\translations\qt_da.qm"
  File "release\translations\qt_de.qm"
  File "release\translations\qt_en.qm"
  File "release\translations\qt_es.qm"
  File "release\translations\qt_fi.qm"
  File "release\translations\qt_fr.qm"
  File "release\translations\qt_gd.qm"
  File "release\translations\qt_he.qm"
  File "release\translations\qt_hu.qm"
  File "release\translations\qt_it.qm"
  File "release\translations\qt_ja.qm"
  File "release\translations\qt_ko.qm"
  File "release\translations\qt_lv.qm"
  File "release\translations\qt_pl.qm"
  File "release\translations\qt_ru.qm"
  File "release\translations\qt_sk.qm"
  File "release\translations\qt_uk.qm"
  File "release\translations\qt_zh_TW.qm"
SectionEnd

Section -AdditionalIcons
  SetOutPath $INSTDIR
  WriteIniStr "$INSTDIR\${PRODUCT_NAME}.url" "InternetShortcut" "URL" "${PRODUCT_WEB_SITE}"
  CreateShortCut "$SMPROGRAMS\Bib2Book\Website.lnk" "$INSTDIR\${PRODUCT_NAME}.url"
  CreateShortCut "$SMPROGRAMS\Bib2Book\Uninstall.lnk" "$INSTDIR\uninst.exe"
SectionEnd

Section -Post
  WriteUninstaller "$INSTDIR\uninst.exe"
  WriteRegStr HKLM "${PRODUCT_DIR_REGKEY}" "" "$INSTDIR\Bib2Book.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayName" "$(^Name)"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "UninstallString" "$INSTDIR\uninst.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayIcon" "$INSTDIR\Bib2Book.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayVersion" "${PRODUCT_VERSION}"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "URLInfoAbout" "${PRODUCT_WEB_SITE}"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "Publisher" "${PRODUCT_PUBLISHER}"
SectionEnd


Function un.onUninstSuccess
  HideWindow
  MessageBox MB_ICONINFORMATION|MB_OK "$(^Name) 已成功地从你的计算机移除。"
FunctionEnd

Function un.onInit
!insertmacro MUI_UNGETLANGUAGE
  MessageBox MB_ICONQUESTION|MB_YESNO|MB_DEFBUTTON2 "你确实要完全移除 $(^Name) ，其及所有的组件？" IDYES +2
  Abort
FunctionEnd

Section Uninstall
  Delete "$INSTDIR\${PRODUCT_NAME}.url"
  Delete "$INSTDIR\uninst.exe"
  Delete "$INSTDIR\translations\qt_zh_TW.qm"
  Delete "$INSTDIR\translations\qt_uk.qm"
  Delete "$INSTDIR\translations\qt_sk.qm"
  Delete "$INSTDIR\translations\qt_ru.qm"
  Delete "$INSTDIR\translations\qt_pl.qm"
  Delete "$INSTDIR\translations\qt_lv.qm"
  Delete "$INSTDIR\translations\qt_ko.qm"
  Delete "$INSTDIR\translations\qt_ja.qm"
  Delete "$INSTDIR\translations\qt_it.qm"
  Delete "$INSTDIR\translations\qt_hu.qm"
  Delete "$INSTDIR\translations\qt_he.qm"
  Delete "$INSTDIR\translations\qt_gd.qm"
  Delete "$INSTDIR\translations\qt_fr.qm"
  Delete "$INSTDIR\translations\qt_fi.qm"
  Delete "$INSTDIR\translations\qt_es.qm"
  Delete "$INSTDIR\translations\qt_en.qm"
  Delete "$INSTDIR\translations\qt_de.qm"
  Delete "$INSTDIR\translations\qt_da.qm"
  Delete "$INSTDIR\translations\qt_cs.qm"
  Delete "$INSTDIR\translations\qt_ca.qm"
  Delete "$INSTDIR\translations\qt_bg.qm"
  Delete "$INSTDIR\translations\qt_ar.qm"
  Delete "$INSTDIR\translations\Bib2Book_en.qm"
  Delete "$INSTDIR\translations\Bib2Book_cn.qm"
  Delete "$INSTDIR\stys\aiceslogos\tongji.png"
  Delete "$INSTDIR\stys\aiceslogos\rwth.pdf"
  Delete "$INSTDIR\stys\aiceslogos\rwth.eps"
  Delete "$INSTDIR\stys\aiceslogos\aices.pdf"
  Delete "$INSTDIR\stys\aiceslogos\aices.eps"
  Delete "$INSTDIR\stys\aicescover.sty"
  Delete "$INSTDIR\styles\qwindowsvistastyle.dll"
  Delete "$INSTDIR\Qt5Widgets.dll"
  Delete "$INSTDIR\Qt5Svg.dll"
  Delete "$INSTDIR\Qt5Gui.dll"
  Delete "$INSTDIR\Qt5Core.dll"
  Delete "$INSTDIR\platforms\qwindows.dll"
  Delete "$INSTDIR\opengl32sw.dll"
  Delete "$INSTDIR\libwinpthread-1.dll"
  Delete "$INSTDIR\libstdc++-6.dll"
  Delete "$INSTDIR\libGLESv2.dll"
  Delete "$INSTDIR\libgcc_s_sjlj-1.dll"
  Delete "$INSTDIR\libgcc_s_seh-1.dll"
  Delete "$INSTDIR\libEGL.dll"
  Delete "$INSTDIR\Install-Fonts.bat"
  Delete "$INSTDIR\imageformats\qwebp.dll"
  Delete "$INSTDIR\imageformats\qwbmp.dll"
  Delete "$INSTDIR\imageformats\qtiff.dll"
  Delete "$INSTDIR\imageformats\qtga.dll"
  Delete "$INSTDIR\imageformats\qsvg.dll"
  Delete "$INSTDIR\imageformats\qjpeg.dll"
  Delete "$INSTDIR\imageformats\qico.dll"
  Delete "$INSTDIR\imageformats\qicns.dll"
  Delete "$INSTDIR\imageformats\qgif.dll"
  Delete "$INSTDIR\iconengines\qsvgicon.dll"
  Delete "$INSTDIR\fonts\cormorant-garamond\OFL.txt"
  Delete "$INSTDIR\fonts\cormorant-garamond\CormorantGaramond-SemiBoldItalic.ttf"
  Delete "$INSTDIR\fonts\cormorant-garamond\CormorantGaramond-SemiBold.ttf"
  Delete "$INSTDIR\fonts\cormorant-garamond\CormorantGaramond-Regular.ttf"
  Delete "$INSTDIR\fonts\cormorant-garamond\CormorantGaramond-MediumItalic.ttf"
  Delete "$INSTDIR\fonts\cormorant-garamond\CormorantGaramond-Medium.ttf"
  Delete "$INSTDIR\fonts\cormorant-garamond\CormorantGaramond-LightItalic.ttf"
  Delete "$INSTDIR\fonts\cormorant-garamond\CormorantGaramond-Light.ttf"
  Delete "$INSTDIR\fonts\cormorant-garamond\CormorantGaramond-Italic.ttf"
  Delete "$INSTDIR\fonts\cormorant-garamond\CormorantGaramond-BoldItalic.ttf"
  Delete "$INSTDIR\fonts\cormorant-garamond\CormorantGaramond-Bold.ttf"
  Delete "$INSTDIR\documentation\figures\project.png"
  Delete "$INSTDIR\documentation\figures\interface.png"
  Delete "$INSTDIR\documentation\example\Zhang dongming 2020-Multivariate probability distribution of shanghai clay properties.pdf"
  Delete "$INSTDIR\documentation\example\PDFs\Zhang dongming 2020-Multivariate probability distribution of shanghai clay properties.pdf"
  Delete "$INSTDIR\documentation\example\PDFs\Liu2016-Multivariate correlation among resilient modulus and cone penetration test parameters of cohesive subgrade soils.pdf"
  Delete "$INSTDIR\documentation\example\PDFs\Feng2019b-Full AccessCorrelation of the hydraulic conductivity of fine-grained soils with water content ratio using a database.pdf"
  Delete "$INSTDIR\documentation\example\PDFs\Feng2019a-A database of saturated hydraulic conductivity of fine-grained soils- probability density functions.pdf"
  Delete "$INSTDIR\documentation\example\PDFs\D’Ignazio2016-Correlations for undrained shear strength of Finnish soft clays.pdf"
  Delete "$INSTDIR\documentation\example\PDFs\Ching2020-Quasi-site-specific prediction for deformation modulus of rock mass.pdf"
  Delete "$INSTDIR\documentation\example\PDFs\Ching2018-Generic transformation models for some intact rock properties.pdf"
  Delete "$INSTDIR\documentation\example\PDFs\Ching2017-Transformation models for effective friction angle and relative density calibrated based on generic database of coarse-grained soils.pdf"
  Delete "$INSTDIR\documentation\example\PDFs\Ching2014-Transformations and correlations among some clay parameters - the global database.pdf"
  Delete "$INSTDIR\documentation\example\PDFs\Ching2014-Modeling piezocone cone penetration (CPTU) parameters of clays as a multivariate normal distribution.pdf"
  Delete "$INSTDIR\documentation\example\PDFs\Ching2014-Correlations among some clay parameters - the multivariate distribution.pdf"
  Delete "$INSTDIR\documentation\example\PDFs\Ching2012-Modeling parameters of structured clays as a multivariate normal distribution.pdf"
  Delete "$INSTDIR\documentation\example\Liu2016-Multivariate correlation among resilient modulus and cone penetration test parameters of cohesive subgrade soils.pdf"
  Delete "$INSTDIR\documentation\example\Feng2019b-Full AccessCorrelation of the hydraulic conductivity of fine-grained soils with water content ratio using a database.pdf"
  Delete "$INSTDIR\documentation\example\Feng2019a-A database of saturated hydraulic conductivity of fine-grained soils- probability density functions.pdf"
  Delete "$INSTDIR\documentation\example\example.tex"
  Delete "$INSTDIR\documentation\example\example.pdf"
  Delete "$INSTDIR\documentation\example\example.b2b"
  Delete "$INSTDIR\documentation\example\D’Ignazio2016-Correlations for undrained shear strength of Finnish soft clays.pdf"
  Delete "$INSTDIR\documentation\example\Cover.tex"
  Delete "$INSTDIR\documentation\example\Cover.pdf"
  Delete "$INSTDIR\documentation\example\Compile.bat"
  Delete "$INSTDIR\documentation\example\Ching2020-Quasi-site-specific prediction for deformation modulus of rock mass.pdf"
  Delete "$INSTDIR\documentation\example\Ching2018-Generic transformation models for some intact rock properties.pdf"
  Delete "$INSTDIR\documentation\example\Ching2017-Transformation models for effective friction angle and relative density calibrated based on generic database of coarse-grained soils.pdf"
  Delete "$INSTDIR\documentation\example\Ching2014-Transformations and correlations among some clay parameters - the global database.pdf"
  Delete "$INSTDIR\documentation\example\Ching2014-Modeling piezocone cone penetration (CPTU) parameters of clays as a multivariate normal distribution.pdf"
  Delete "$INSTDIR\documentation\example\Ching2014-Correlations among some clay parameters - the multivariate distribution.pdf"
  Delete "$INSTDIR\documentation\example\Ching2012-Modeling parameters of structured clays as a multivariate normal distribution.pdf"
  Delete "$INSTDIR\documentation\example\aiceslogos\tongji.png"
  Delete "$INSTDIR\documentation\example\aiceslogos\rwth.pdf"
  Delete "$INSTDIR\documentation\example\aiceslogos\rwth.eps"
  Delete "$INSTDIR\documentation\example\aiceslogos\aices.pdf"
  Delete "$INSTDIR\documentation\example\aiceslogos\aices.eps"
  Delete "$INSTDIR\documentation\example\aicescover.sty"
  Delete "$INSTDIR\documentation\doc.tex"
  Delete "$INSTDIR\documentation\doc.pdf"
  Delete "$INSTDIR\D3Dcompiler_47.dll"
  Delete "$INSTDIR\Compile.bat"
  Delete "$INSTDIR\Bib2Book.exe"

  Delete "$SMPROGRAMS\Bib2Book\Uninstall.lnk"
  Delete "$SMPROGRAMS\Bib2Book\Website.lnk"
  Delete "$DESKTOP\Bib2Book.lnk"
  Delete "$SMPROGRAMS\Bib2Book\Bib2Book.lnk"

  RMDir "$SMPROGRAMS\Bib2Book"
  RMDir "$INSTDIR\translations"
  RMDir "$INSTDIR\stys\aiceslogos"
  RMDir "$INSTDIR\stys"
  RMDir "$INSTDIR\styles"
  RMDir "$INSTDIR\platforms"
  RMDir "$INSTDIR\imageformats"
  RMDir "$INSTDIR\iconengines"
  RMDir "$INSTDIR\fonts\cormorant-garamond"
  RMDir "$INSTDIR\documentation\figures"
  RMDir "$INSTDIR\documentation\example\PDFs"
  RMDir "$INSTDIR\documentation\example\aiceslogos"
  RMDir "$INSTDIR\documentation\example"
  RMDir "$INSTDIR\documentation"
  RMDir "$INSTDIR"

  DeleteRegKey ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}"
  DeleteRegKey HKLM "${PRODUCT_DIR_REGKEY}"
  SetAutoClose true
SectionEnd