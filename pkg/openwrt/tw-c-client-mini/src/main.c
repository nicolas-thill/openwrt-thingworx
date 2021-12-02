#include <twExt.h>
#include <stdio.h>
#include <unistd.h>

extern twConfig twcfg;
twConfig *twConf = &twcfg;

#define TW_HOST "192.168.69.170"
#define TW_APP_KEY "0c8de122-676f-45c6-9294-aaf12d3258f1"
#define DATA_COLLECTION_RATE_MSEC 5000

#define RETRY_COUNT 3

#if defined NO_TLS
	#define TW_PORT 8080
#else
	#define TW_PORT 8443
#endif

char *me;
char myHostName[HOST_NAME_MAX + 1];
char *twHost = TW_HOST;
int twPort =  TW_PORT;
char *twAppKey = TW_APP_KEY;
char *twName = myHostName;

void twAppKeyCallback(char* appKeyBuffer, unsigned int maxLength);
void twBindEventHandler(char* entityName, char isBound, void* userData);
void twSyncStateHandler(char *entityName, twInfoTable *subscriptionInfo, void *userData);

extern void createClientThing(char* thingName);

static void printCommandLineUsage(char* command) {
	static char usage[] =
		"Usage: %1$s [OPTIONS]\n"
		"  Options:\n"
		"    -H HOST    Address of the ThingWorx instance\n"
		"                 (Defaults to \"%2$s\")\n"
		"    -P PORT    Port number of the ThingWorx instance\n"
		"                 (Defaults to \"%3$d\")\n"
		"    -K KEY     Application key for the ThingWorx instance\n"
		"                 (Defaults to an invalid key)\n"
		"    -N NAME    The name that will be associated with this Thing\n"
		"                 (Defaults to hostname: \"%4$s\")\n"
		"    -s         Use secure connection (SSL/TLS)\n"
		"    -d         Increase logging level\n"
		"                 (Defaults to ERROR log level)\n"
		"    -v         Be verbose\n"
		"\n"
		"    -?, -h    display usage information and exit\n"
		"\n";

	printf(usage, command, TW_HOST, TW_PORT, myHostName);
}

void twAppKeyCallback(char* appKeyBuffer, unsigned int maxLength) {
	strncpy(appKeyBuffer, twAppKey, maxLength);
}

void twBindEventHandler(char* entityName, char isBound, void* userData) {
	TW_LOG(TW_FORCE, "BindEventHandler: Entity %s was %s", entityName, isBound ? "Bound" : "Unbound");
}

void twSyncStateHandler(char *entityName, twInfoTable *subscriptionInfo, void *userData){
	/*
	 * Called after binding to notify your application about what fields are bound on the server.
	 * Will also be called each time bindings on a thing are edited.
	 */
	TW_LOG(TW_FORCE,"twSyncStateHandler: Entity %s was synchronized with your ThingWorx Server", entityName);
}

int main(int argc, char** argv)
{
	int opt = 0;
	int err = 0;
	int log_level = TW_ERROR;
	int log_verbose = FALSE;
	int secure = FALSE;

	gethostname(myHostName, sizeof(myHostName));

	while ((opt = getopt(argc, argv, "H:P:K:N:dsv?h")) != -1) {
		switch (opt) {
		case 'H':
			twHost = optarg;
			break;
		case 'P':
			twPort = atoi(optarg);
			break;
		case 'K':
			twAppKey = optarg;
			break;
		case 'N':
			twName = optarg;
			break;
		case 'd':
			if (log_level > 0) {
				log_level--;
			}
			break;
		case 's':
			secure = TRUE;
			break;
		case 'v':
			log_verbose = TRUE;
			break;
		case '?':
		case 'h':
			printCommandLineUsage(argv[0]);
			exit(EXIT_SUCCESS);
			break;
		default: /* '?' */
			printCommandLineUsage(argv[0]);
			exit(EXIT_FAILURE);
		}
	}

	twLogger_SetLevel(log_level);
	twLogger_SetIsVerbose(log_verbose);

	TW_LOG(TW_FORCE, "Starting up...");

	twConf->enable_tls_hostname_validation = FALSE;

	err = twApi_Initialize(twHost, twPort, TW_URI, twAppKeyCallback, NULL, MESSAGE_CHUNK_SIZE, MESSAGE_CHUNK_SIZE, TRUE);
	if (err) {
		TW_LOG(TW_ERROR, "Error initializing the API");
		exit(err);
	}

	if (!secure) {
		twApi_DisableEncryption();
	}

	twApi_RegisterBindEventCallback(twName, twBindEventHandler, TW_NO_USER_DATA); /* Callbacks only when thingName is bound/unbound */
	twApi_RegisterSynchronizeStateEventCallback(NULL, twSyncStateHandler, TW_NO_USER_DATA);

	createClientThing(twName);

	err = twApi_Connect(CONNECT_TIMEOUT, RETRY_COUNT);
	if (err) {
		TW_LOG(TW_ERROR, "main: Server connection failed after %d attempts.  Error Code: %d", RETRY_COUNT, err);
	}

	twExt_Idle(DATA_COLLECTION_RATE_MSEC, TW_THREADING_MULTI, 5);

	twApi_Delete();
}
