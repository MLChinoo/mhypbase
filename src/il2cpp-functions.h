using namespace app;

DO_APP_FUNC(0, LPVOID, System__Text__EncodingHelper_GetDefaultEncoding, ());
DO_APP_FUNC(0, LPVOID, System__Text__Encoding_GetBytes, (LPVOID __this, LPVOID str));
DO_APP_FUNC(0, LPVOID, MiHoYo__SDK__SDKUtil_RSAEncrypt, (LPVOID publicKey, LPVOID content));
DO_APP_FUNC(0, LPVOID, MoleMole__MoleMoleSecurity_GetPublicRSAKey, ());
DO_APP_FUNC(0, LPVOID, MoleMole__MoleMoleSecurity_GetPrivateRSAKey, ());
DO_APP_FUNC(0, LPVOID, MoleMole__RSAUtil_RSAEncrypt, (LPVOID key, LPVOID data));
DO_APP_FUNC(0, LPVOID, MoleMole__RSAUtil_RSADecrypt, (LPVOID key, LPVOID data));
DO_APP_FUNC(0, LPVOID, MoleMole__RSAUtil_RSAVerifyHash, (LPVOID key, LPVOID bytes, LPVOID sign));
DO_APP_FUNC(0, LPVOID, MoleMole__RSAUtil_RSAVerifyData, (LPVOID key, LPVOID bytes, LPVOID sign));
DO_APP_FUNC(0, LPVOID, UnityEngine__JsonUtility_FromJson, (LPVOID json, LPVOID type, LPVOID method));
DO_APP_FUNC(0, LPVOID, MoleMole__ConfigUtil_LoadJSONStrConfig, (LPVOID jsonText, LPVOID useJsonUtility, LPVOID method));
DO_APP_FUNC(0, LPVOID, MoleMole__Miscs_GetConfigChannel, ());
DO_APP_FUNC(0, LPVOID, MoleMole__Miscs_LoadChannelConfigBlk, ());
DO_APP_FUNC(0, LPVOID, MoleMole__FightModule_OnWindSeedClientNotify, (LPVOID __this, LPVOID notify));
DO_APP_FUNC(0, LPVOID, MoleMole__PlayerModule_OnWindSeedClientNotify, (LPVOID __this, LPVOID notify));
DO_APP_FUNC(0, LPVOID, MoleMole__PlayerModule_OnReciveLuaShell, (LPVOID __this, LPVOID notify));
