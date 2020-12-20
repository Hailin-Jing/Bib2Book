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
!insertmacro MUI_PAGE_FINISH

; Uninstaller pages
!insertmacro MUI_UNPAGE_INSTFILES

; Language files
!insertmacro MUI_LANGUAGE "English"
!insertmacro MUI_LANGUAGE "SimpChinese"

; MUI end ------

Name "${PRODUCT_NAME} ${PRODUCT_VERSION}"
OutFile "Setup.exe"
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
  File "release\D3Dcompiler_47.dll"
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
  File "release\libEGL.dll"
  File "release\libGLESv2.dll"
  File "release\opengl32sw.dll"
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
  MessageBox MB_ICONINFORMATION|MB_OK "$(^Name) �ѳɹ��ش���ļ�����Ƴ���"
FunctionEnd

Function un.onInit
!insertmacro MUI_UNGETLANGUAGE
  MessageBox MB_ICONQUESTION|MB_YESNO|MB_DEFBUTTON2 "��ȷʵҪ��ȫ�Ƴ� $(^Name) ���估���е������" IDYES +2
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
  Delete "$INSTDIR\libGLESv2.dll"
  Delete "$INSTDIR\libEGL.dll"
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
  Delete "$INSTDIR\D3Dcompiler_47.dll"
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
  RMDir "$INSTDIR"

  DeleteRegKey ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}"
  DeleteRegKey HKLM "${PRODUCT_DIR_REGKEY}"
  SetAutoClose true
SectionEnd