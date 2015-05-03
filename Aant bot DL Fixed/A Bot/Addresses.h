//Addresses as of GMS v.83
#define CharBase      0x00bebf98	// A1 ?? ?? ?? ?? 3B C7 ?? ?? 8D 8D ?? ?? ?? ?? 51
#define CharXOffset   0x116c		// 89 8B ?? ?? ?? ?? 68 ?? ?? ?? ?? 8D 4D ?? 89 83 ?? ?? ?? ?? E8 ?? ?? ?? ?? 6A 03 56 8D 4D ??
#define CharYOffset   0x1170		// 89 86 ?? ?? ?? ?? 89 9E ?? ?? ?? ?? 5F 5E 5B C3 8B C1 
#define MouseBase	  0x????????	
#define MouseXOffset  0x???
#define MouseYOffset  0x???
#define MobBase       0x00bebfa4	// 8B 0D ?? ?? ?? ?? FF 75 ?? E8 ?? ?? ?? ?? 8B F0 33 DB 3B F3
#define MobOffset     0x24			// 8A 9C 00 ?? ?? ?? ?? EB ?? 9C 00 25 ?? ?? ?? ??
#define PeopleBase    0x00bebfa8	// 8B 0D ?? ?? ?? ?? E8 ?? ?? ?? ?? 8B F0 3B F7 75 ?? 8D 45 ?? 68 ?? ?? ?? ?? 50 // First Addy
#define PeopleOffset  0x18			// 29 9C 00 ?? ?? ?? ?? D8 29 9C 00 18 00 00 00 E3
#define ItemBase      0x00bed6ac	// 89 0D ?? ?? ?? ?? 6A 1F 5A 6A 64 33 FF 89 38 59 6a ??
#define ItemOffset    0x14			// 29 9C 00 ?? ?? ?? ?? AF 29 9C 00 ?? ?? ?? ?? // First Addy
#define AttackBase    0x00bebf98	// A1 ?? ?? ?? ?? 3B C7 ?? ?? 8D 8D ?? ?? ?? ??
#define AttackOffset  0x2B88		// 8D 8B ? ? ? ? C6 45 FC 05 E8 ? ? ? ? 39 BB ? ? ? ?   offset- 0x10 
#define ServerBase    0x00be7918	// 8B 0D ?? ?? ?? ?? 8D 45 ?? 50 E8 ?? ?? ?? ?? 83 7D ?? ?? 8B 70 ?? 74 ?? 6A ?? 8D ?? // First Addy (0=Scania, 1= Bera, etc.)
#define ServerOffset  0x2054		// 8B 9E ?? ?? ?? ?? 8D 45 ?? 68 ?? ?? ?? ?? // First Addy
#define MapIDBase     0x00bed788    // A1 ?? ?? ?? ?? 3B C7 89 7D ?? 74 ?? 8B 40 ??
#define MapIDOffset   0x668			// 8D 86 ?? ?? ?? ?? 50 C6 45 ?? ?? E8 ?? ?? ?? ?? 57 53 6A ?? // Bottom Addy //8D 8E ? ? ? ? C6 ? ? ? E8 ? ? ? ? 8B ? ? 8B 10 8D ? ? 51 6A ? 68 ? ? ? ? 6A ? 68 ? ? ? ? 56 8B C8 FF 52 ? 8D 45 ? 68 ? ? ? ? 50 E8 ? ? ? ? 5th from last
#define ChannelBase   0x00be7918	// 8B 35 ?? ?? ?? ?? 8B 86 ?? ?? ?? ?? 57 8B 7D ?? 
#define ChannelOffset 0x2058		// 8B 86 ?? ?? ?? ?? 57 8B 7D ?? 8D 9E ?? ?? ?? ?? 89 4D ??
#define CharstatBase  0x00bec208	// A1 ? ? ? ? C3 8B 01 85 C0 74 06 8B 08 50 
#define HpOffset	  0xD18			// 8B 86 ?? ?? ?? ?? 3B 45 ?? 8D BE ?? ?? ?? ?? // First Addy
#define MpOffset	  0xD1C			// HpOffSet+4
#define CharWarnBase  0x00bebf9c	// 8B 0D ?? ?? ?? ?? 89 41 ?? 39 BB ?? ?? ?? ?? 75 ??
#define WarnHpOffset  0x7C			// WarnMpOffset - 0x4
#define WarnMpOffset  0x80			// FF 91 ?? ?? ?? ?? 85 C0 7D ?? 68 ?? ?? ?? ?? FF 75 ?? 50 E8 ?? ?? ?? ?? C6 45 ?? ?? 8D 45 ?? E9 ?? ?? ?? ?? // First Addy
#define BreatheBase   0x00bebf98	// A1 ?? ?? ?? ?? 3B C7 ?? ?? 8D 8D ?? ?? ?? ?? 51
#define BreatheOffset 0x55C
//#define AutoCC_Hook	  0x007F7F3D	 //8B 80 ? ? ? ? 83 F8 ? 74 ? 83 F8 ? 74 ? 39
//#define AutoCC_Call	  0x0097fd3c	 //B8 ? ? ? 00 E8 ? ? ? 00 83 EC ? 56 8B 35 ? ? ? 00 57 33 ff 57 68
//-------------------------------------------------------------------------------------------------------------------------
#define StatHookCallAddy  0x008D8247;// E8 ?? ?? ?? 00 8B 4D F0 E8 ?? ?? ?? 00 85 C0
#define DecrypterCallAddy 0x008D850B;// B8 ?? ?? ?? 00 E8 ?? ?? ?? 00 81 EC ?? 00 00 00 A1 ?? ?? ?? 00 8B // 2nd addy
//-------------------------------------------------------------------------------------------------------------------------
#define LogInAddy		     0x00bf1650	//39 1D ?? ?? ?? ?? 74 ?? A1 ? ? ? ? 8B 00 EB ?? 33 C0 3B C3 74 ?? 50 8B CE

//Credits to Cam1596 for the following Pointers
#define Login_Stage_1_Base   0x00bec20c	//8B 0D ? ? ? ? 6A 00 8D 45 ? 50 E8 ? ? ? ? 8D 45 ? 50 8D 45 ? 50 
#define Login_Stage_1_Offset 0x74		//83 79 ? 00 53 56 57 74 07 8B 41 ? 8B 30 EB 02 33 F6 85 F6 89 75 F8 0F 84
#define Login_Stage_2_Base   0x00beded4 //8B 35 ? ? ? ? 85 F6 74 ? 8B 46 ? 8D 4E ? 68 ? ? ? ? FF 50 ? 85 
#define Login_Stage_2_Offset 0x168		//8B 86 ? ? ? ? 83 F8 ? 75
//-------------------------------------------------------------------------------------------------------------------------
#define SuperTubiAddy        0x00485C01 //75 ? 83 7C 24 ? ? 75 ? 8B ? ? ? ? ? FF 70 ? 83 C0 ? 50 
#define SevenMissGModeAddy   0x0095831F //0F ? ? ? ? ? 8B 47 ? 8D 4F ? FF 50 ? 8B 30 8B ? ? 8D 48 ? 8B 01 FF 50 ? 3B 30 7E ?
#define SevenMissGModeAddy_2 0x009591ca //Original Addy to jump to.
#define DemVacAddy			 0x006685DC	//89 ? ? ? ? ? 89 ? ? ? ? ? 8D ? ? 50 FF 15 ? ? ? ? 8D ? ? 68 ? ? ? ? 50 E8 ? ? ? ? 3B C7 59 59 7D 06 // first addy
#define SendAddyAddy		 0x004963B4	//B8 ? ? ? 0 E8 ? ? ? 0 51 56 57 8B F9 8D 77 ? 8B CE 89 ? ? E8 ? ? ? ? 8B 47
#define ClassAddyAddy		 0x004729B6 //8b 0d ? ? ? ? 83 65 ? ? 8d 45 ? 50 e8 ? ? ? ? 83 4d ? ? 8d 4d ? c7 46
