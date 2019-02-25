@echo 1. Build Test Cert and Test Software Publishing Certificate
MakeCert -sv sign.pvk -r -n "CN=ItsTest" sign.cer
Cert2SPC sign.cer sign.spc
@echo
#echo 2. Build another self-signed certificate Software Publishing Certificate
MakeCert -sv test.pvk -r -n "CN=ItsTest1" test.cer
Cert2SPC test.cer test.spc
@echo
@echo 3. Build the Certificate Trust List
MakeCTL test.cer test.ctl
@echo
@echo 4. Sign test.ctl with sign.pvk and sign.spc
SignCode -v sign.pvk -spc sign.spc test.ctl
@echo
@echo 5. Move sign.cer to the trust system store
CertMgr -add -ctl test.ctl -s trust
@echo 
@echo 6. Move sign.cer to the root system store
CertMgr -add -c sign.cer -s root
@echo
@echo 7. SIgn something (test.exe) with test.pvk, and test.spc
SignCode -v test.pvk -spc test.spc test.exe
@echo
@echo Since test.cer is in the test.ctl, ChkTrust should succeed
ChkTrust test.exe

makecert -sv sign.pvk -r -n "CN=ItsTest" sign.cer
cert2spc sign.cer sign.spc
pvk2pfx -pvk sign.pvk -spc sign.spc -pfx sign.pfx -po <password>
makecert -sv test.pvk -r -n "CN=ItsTest1" test.cer
cert2spc test.cer test.spc
makectl test.cer test.ctl
pvk2pfx -pvk test.pvk -spc test.spc -pfx test.pfx -po <password>
signtool sign -f sign.pfx -p <password> -v test.ctl
certmgr -add -ctl test.ctl -s trust
certmgr -add -c sign.cer -s root
signtool sign -f test.pfx -v test.exe
signtool verify -a -v test.exe



C:\Documents and Settings\Mike Burnett\My Documents\Projects\Vector4>signtool si
gn -f sign.pfx -p butthead -v AdvancedAlignedVector.dll
The following certificate was selected:
    Issued to: ItsTest
    Issued by: ItsTest
    Expires:   12/31/2039 3:59:59 PM
    SHA1 hash: 95B52329B0C81732B300F2EC1DD8671FF97023EC

C:\Documents and Settings\Mike Burnett\My Documents\Projects\Vector4>signtool si
gn -f sign.pfx -p butthead -v AdvancedUnalignedVector.dll
The following certificate was selected:
    Issued to: ItsTest
    Issued by: ItsTest
    Expires:   12/31/2039 3:59:59 PM
    SHA1 hash: 95B52329B0C81732B300F2EC1DD8671FF97023EC

C:\Documents and Settings\Mike Burnett\My Documents\Projects\Vector4>signtool si
gn -f sign.pfx -p butthead -v AlignedVector.dll
The following certificate was selected:
    Issued to: ItsTest
    Issued by: ItsTest
    Expires:   12/31/2039 3:59:59 PM
    SHA1 hash: 95B52329B0C81732B300F2EC1DD8671FF97023EC

Done Adding Additional Store

