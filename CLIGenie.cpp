#include "Genie.h"
#include <iostream>
#include <vector>
#include <unordered_set>
#include <array>

using namespace std;

unordered_set<string> df_dm_list{
		"06_2AH",
		"06_2DH",
		"06_3AH",
		"06_3CH",
		"06_3DH",
		"06_3EH",
		"06_3FH",
		"06_45H",
		"06_46H",
		"06_47H",
		"06_4EH",
		"06_4FH",
		"06_55H",
		"06_56H",
		"06_5EH",
		"06_66H",
		"06_6AH",
		"06_6CH",
		"06_7DH",
		"06_7EH",
		"06_8CH",
		"06_8DH",
		"06_8EH",
		"06_8FH",
		"06_97H",
		"06_9AH",
		"06_9EH",
		"06_A5H",
		"06_A6H",
		"06_BFH"
};

void print_help() {


	cout << "********************************************Notice**********************************************\n";
	cout << "LLNL collated this information from The Intel64 and IA-32 Architecture Software Developer's\n"
		 << "Manual Volume 4:  Model-Specific Registers from [March 2023] document number [335592-079US].\n"
		 <<	"While we took due care in its transcription, we might have made mistake or several.\n"
		 << "For the most recent an authoritative documentation, please consult the most recent version of\n"
		 <<	"Volume 4 at https://www.intel.com/content/www/us/en/developer/articles/technical/intel-sdm.html\n"
		 <<	"Corrections and amplifications are most welcome.\n\n"
		 <<	"Also note that processor firmware may choose to disallow access to particular MSRs. The fact\n"
		 <<	"that an MSR is listed here for a particular processor model does not guarantee that it will be\n"
		 << "accessible on your processor.\n";

	cout << "************************************************************************************************\n";
	cout << "Incorrect usage! use one of the following options\n";
	cout << "Print list of supported df_dms: ./GenieCLI supported\n";
	cout << "Print MSR list for df_dm: ./GenieCLI msr df_dm\n";
	cout << "Print df_dm list for MSR: ./GenieCLI df_dm MSR\n";
	cout << "Print bit-mask: ./GenieCLI bitmask df_dm MSR\n";
	cout << "Dump all DataStore values: ./debug\n";
	cout << "************************************************************************************************\n";

}

void print_msr(vector<array<string, 5> > &df_dm_ret, string df_dm){
	for(const auto & row : df_dm_ret) {
		std::cout << "Hex address: " << setw(12) << row[0] << "\tMSR name: " << row[1] << "\tDomain: " << row[2] << "\tDescription: " << row[3] << "\tTable: " <<row[4] << "\n";
	}
	std::cout << "number of entries for " << df_dm << ": " << df_dm_ret.size() << "\n";
	std::cout << "------------------------------------------------------------------------------------------------------------------------------------------------------\n";
}

void print_df_dm(vector<string> &df_dms, string msr){
	std::cout << "number of dfdms associated with MSR " << msr << ": " << std::to_string(df_dms.size()) << "\n";
	for(auto & dfdm : df_dms) {
		std::cout << dfdm << " ";
	}
	cout << "\n";
}

void print_bitmask(array<string, 3> &bitmask_ret) {
	cout << "MSR address: " << setw(18) << bitmask_ret[0] << setw(18) << "\tMASK: " << bitmask_ret[1] << "\t Table: " << bitmask_ret[2] << "\n";
}


int main(int argc, char *argv[])
{
	GenieDataManager manager;
	if (argc < 2 or argc > 4)
	{
		print_help();
		return -1;

	} else if(strcmp(argv[1], "msr") == 0) {
		
		if (argc != 3) {
			print_help();
			return -1;
		}

		if (df_dm_list.find(argv[2]) != df_dm_list.end()) {
			auto df_dm_ret = manager.getMSRsForDFDM(argv[2]);
			print_msr(df_dm_ret, argv[2]);
		} else {
			cout << "the df_dm you entered is not supported! Please make sure the df_dm is correct and in capital letters\n";
			return -1;
		}

	} else if (strcmp(argv[1], "df_dm") == 0) {

		if (argc != 3) {
			print_help();
			return -1;
		}
		
		auto ret = manager.getDFDMsForMSR(argv[2]);
		print_df_dm(ret, argv[2]);

	} else if (strcmp(argv[1], "bitmask") == 0) {

		if (argc != 4) {
			print_help();
			return -1;
		}

		auto ret = manager.getMask(argv[2], argv[3]);
		print_bitmask(ret);

	} else if (strcmp(argv[1], "supported") == 0){
		
		for (auto & df_dm : df_dm_list){
			cout << df_dm << "\n";
		}

	} else if (strcmp(argv[1], "debug") == 0) {
	
		manager.debug();

	} else {
		
		print_help();
		return -1;
	}

	return 0;

}




