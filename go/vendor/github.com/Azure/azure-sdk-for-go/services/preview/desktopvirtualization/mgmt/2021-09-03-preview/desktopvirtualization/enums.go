package desktopvirtualization

// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See License.txt in the project root for license information.
//
// Code generated by Microsoft (R) AutoRest Code Generator.
// Changes may cause incorrect behavior and will be lost if the code is regenerated.

// ApplicationGroupType enumerates the values for application group type.
type ApplicationGroupType string

const (
	// ApplicationGroupTypeDesktop ...
	ApplicationGroupTypeDesktop ApplicationGroupType = "Desktop"
	// ApplicationGroupTypeRemoteApp ...
	ApplicationGroupTypeRemoteApp ApplicationGroupType = "RemoteApp"
)

// PossibleApplicationGroupTypeValues returns an array of possible values for the ApplicationGroupType const type.
func PossibleApplicationGroupTypeValues() []ApplicationGroupType {
	return []ApplicationGroupType{ApplicationGroupTypeDesktop, ApplicationGroupTypeRemoteApp}
}

// ApplicationType enumerates the values for application type.
type ApplicationType string

const (
	// ApplicationTypeDesktop ...
	ApplicationTypeDesktop ApplicationType = "Desktop"
	// ApplicationTypeRemoteApp ...
	ApplicationTypeRemoteApp ApplicationType = "RemoteApp"
)

// PossibleApplicationTypeValues returns an array of possible values for the ApplicationType const type.
func PossibleApplicationTypeValues() []ApplicationType {
	return []ApplicationType{ApplicationTypeDesktop, ApplicationTypeRemoteApp}
}

// CommandLineSetting enumerates the values for command line setting.
type CommandLineSetting string

const (
	// CommandLineSettingAllow ...
	CommandLineSettingAllow CommandLineSetting = "Allow"
	// CommandLineSettingDoNotAllow ...
	CommandLineSettingDoNotAllow CommandLineSetting = "DoNotAllow"
	// CommandLineSettingRequire ...
	CommandLineSettingRequire CommandLineSetting = "Require"
)

// PossibleCommandLineSettingValues returns an array of possible values for the CommandLineSetting const type.
func PossibleCommandLineSettingValues() []CommandLineSetting {
	return []CommandLineSetting{CommandLineSettingAllow, CommandLineSettingDoNotAllow, CommandLineSettingRequire}
}

// CreatedByType enumerates the values for created by type.
type CreatedByType string

const (
	// CreatedByTypeApplication ...
	CreatedByTypeApplication CreatedByType = "Application"
	// CreatedByTypeKey ...
	CreatedByTypeKey CreatedByType = "Key"
	// CreatedByTypeManagedIdentity ...
	CreatedByTypeManagedIdentity CreatedByType = "ManagedIdentity"
	// CreatedByTypeUser ...
	CreatedByTypeUser CreatedByType = "User"
)

// PossibleCreatedByTypeValues returns an array of possible values for the CreatedByType const type.
func PossibleCreatedByTypeValues() []CreatedByType {
	return []CreatedByType{CreatedByTypeApplication, CreatedByTypeKey, CreatedByTypeManagedIdentity, CreatedByTypeUser}
}

// HealthCheckName enumerates the values for health check name.
type HealthCheckName string

const (
	// HealthCheckNameAppAttachHealthCheck Verifies that the AppAttachService is healthy (there were no issues
	// during package staging). The AppAttachService is used to enable the staging/registration (and eventual
	// deregistration/destaging) of MSIX apps that have been set up by the tenant admin. This checks whether
	// the component had any failures during package staging. Failures in staging will prevent some MSIX apps
	// from working properly for the end user. If this check fails, it is non fatal and the machine still can
	// service connections, main issue may be certain apps will not work for end-users.
	HealthCheckNameAppAttachHealthCheck HealthCheckName = "AppAttachHealthCheck"
	// HealthCheckNameDomainJoinedCheck Verifies the SessionHost is joined to a domain. If this check fails is
	// classified as fatal as no connection can succeed if the SessionHost is not joined to the domain.
	HealthCheckNameDomainJoinedCheck HealthCheckName = "DomainJoinedCheck"
	// HealthCheckNameDomainReachable Verifies the domain the SessionHost is joined to is still reachable. If
	// this check fails is classified as fatal as no connection can succeed if the domain the SessionHost is
	// joined is not reachable at the time of connection.
	HealthCheckNameDomainReachable HealthCheckName = "DomainReachable"
	// HealthCheckNameDomainTrustCheck Verifies the SessionHost is not experiencing domain trust issues that
	// will prevent authentication on SessionHost at connection time when session is created. If this check
	// fails is classified as fatal as no connection can succeed if we cannot reach the domain for
	// authentication on the SessionHost.
	HealthCheckNameDomainTrustCheck HealthCheckName = "DomainTrustCheck"
	// HealthCheckNameFSLogixHealthCheck Verifies the FSLogix service is up and running to make sure users'
	// profiles are loaded in the session. If this check fails is classified as fatal as even if the connection
	// can succeed, user experience is bad as the user profile cannot be loaded and user will get a temporary
	// profile in the session.
	HealthCheckNameFSLogixHealthCheck HealthCheckName = "FSLogixHealthCheck"
	// HealthCheckNameMetaDataServiceCheck Verifies the metadata service is accessible and return compute
	// properties.
	HealthCheckNameMetaDataServiceCheck HealthCheckName = "MetaDataServiceCheck"
	// HealthCheckNameMonitoringAgentCheck Verifies that the required Geneva agent is running. If this check
	// fails, it is non fatal and the machine still can service connections, main issue may be that monitoring
	// agent is missing or running (possibly) older version.
	HealthCheckNameMonitoringAgentCheck HealthCheckName = "MonitoringAgentCheck"
	// HealthCheckNameSupportedEncryptionCheck Verifies the value of SecurityLayer registration key. If the
	// value is 0 (SecurityLayer.RDP) this check fails with Error code = NativeMethodErrorCode.E_FAIL and is
	// fatal. If the value is 1 (SecurityLayer.Negotiate) this check fails with Error code =
	// NativeMethodErrorCode.ERROR_SUCCESS and is non fatal.
	HealthCheckNameSupportedEncryptionCheck HealthCheckName = "SupportedEncryptionCheck"
	// HealthCheckNameSxSStackListenerCheck Verifies that the SxS stack is up and running so connections can
	// succeed. If this check fails is classified as fatal as no connection can succeed if the SxS stack is not
	// ready.
	HealthCheckNameSxSStackListenerCheck HealthCheckName = "SxSStackListenerCheck"
	// HealthCheckNameUrlsAccessibleCheck Verifies that the required WVD service and Geneva URLs are reachable
	// from the SessionHost. These URLs are: RdTokenUri, RdBrokerURI, RdDiagnosticsUri and storage blob URLs
	// for agent monitoring (geneva). If this check fails, it is non fatal and the machine still can service
	// connections, main issue may be that monitoring agent is unable to store warm path data (logs, operations
	// ...).
	HealthCheckNameUrlsAccessibleCheck HealthCheckName = "UrlsAccessibleCheck"
	// HealthCheckNameWebRTCRedirectorCheck Verifies whether the WebRTCRedirector component is healthy. The
	// WebRTCRedirector component is used to optimize video and audio performance in Microsoft Teams. This
	// checks whether the component is still running, and whether there is a higher version available. If this
	// check fails, it is non fatal and the machine still can service connections, main issue may be the
	// WebRTCRedirector component has to be restarted or updated.
	HealthCheckNameWebRTCRedirectorCheck HealthCheckName = "WebRTCRedirectorCheck"
)

// PossibleHealthCheckNameValues returns an array of possible values for the HealthCheckName const type.
func PossibleHealthCheckNameValues() []HealthCheckName {
	return []HealthCheckName{HealthCheckNameAppAttachHealthCheck, HealthCheckNameDomainJoinedCheck, HealthCheckNameDomainReachable, HealthCheckNameDomainTrustCheck, HealthCheckNameFSLogixHealthCheck, HealthCheckNameMetaDataServiceCheck, HealthCheckNameMonitoringAgentCheck, HealthCheckNameSupportedEncryptionCheck, HealthCheckNameSxSStackListenerCheck, HealthCheckNameUrlsAccessibleCheck, HealthCheckNameWebRTCRedirectorCheck}
}

// HealthCheckResult enumerates the values for health check result.
type HealthCheckResult string

const (
	// HealthCheckResultHealthCheckFailed Health check failed.
	HealthCheckResultHealthCheckFailed HealthCheckResult = "HealthCheckFailed"
	// HealthCheckResultHealthCheckSucceeded Health check passed.
	HealthCheckResultHealthCheckSucceeded HealthCheckResult = "HealthCheckSucceeded"
	// HealthCheckResultSessionHostShutdown We received a Shutdown notification.
	HealthCheckResultSessionHostShutdown HealthCheckResult = "SessionHostShutdown"
	// HealthCheckResultUnknown Health check result is not currently known.
	HealthCheckResultUnknown HealthCheckResult = "Unknown"
)

// PossibleHealthCheckResultValues returns an array of possible values for the HealthCheckResult const type.
func PossibleHealthCheckResultValues() []HealthCheckResult {
	return []HealthCheckResult{HealthCheckResultHealthCheckFailed, HealthCheckResultHealthCheckSucceeded, HealthCheckResultSessionHostShutdown, HealthCheckResultUnknown}
}

// HostPoolType enumerates the values for host pool type.
type HostPoolType string

const (
	// HostPoolTypeBYODesktop Users assign their own machines, load balancing logic remains the same as
	// Personal. PersonalDesktopAssignmentType must be Direct.
	HostPoolTypeBYODesktop HostPoolType = "BYODesktop"
	// HostPoolTypePersonal Users will be assigned a SessionHost either by administrators
	// (PersonalDesktopAssignmentType = Direct) or upon connecting to the pool (PersonalDesktopAssignmentType =
	// Automatic). They will always be redirected to their assigned SessionHost.
	HostPoolTypePersonal HostPoolType = "Personal"
	// HostPoolTypePooled Users get a new (random) SessionHost every time it connects to the HostPool.
	HostPoolTypePooled HostPoolType = "Pooled"
)

// PossibleHostPoolTypeValues returns an array of possible values for the HostPoolType const type.
func PossibleHostPoolTypeValues() []HostPoolType {
	return []HostPoolType{HostPoolTypeBYODesktop, HostPoolTypePersonal, HostPoolTypePooled}
}

// LoadBalancerType enumerates the values for load balancer type.
type LoadBalancerType string

const (
	// LoadBalancerTypeBreadthFirst ...
	LoadBalancerTypeBreadthFirst LoadBalancerType = "BreadthFirst"
	// LoadBalancerTypeDepthFirst ...
	LoadBalancerTypeDepthFirst LoadBalancerType = "DepthFirst"
	// LoadBalancerTypePersistent ...
	LoadBalancerTypePersistent LoadBalancerType = "Persistent"
)

// PossibleLoadBalancerTypeValues returns an array of possible values for the LoadBalancerType const type.
func PossibleLoadBalancerTypeValues() []LoadBalancerType {
	return []LoadBalancerType{LoadBalancerTypeBreadthFirst, LoadBalancerTypeDepthFirst, LoadBalancerTypePersistent}
}

// Operation enumerates the values for operation.
type Operation string

const (
	// OperationComplete Complete the migration.
	OperationComplete Operation = "Complete"
	// OperationHide Hide the hostpool.
	OperationHide Operation = "Hide"
	// OperationRevoke Revoke the migration.
	OperationRevoke Operation = "Revoke"
	// OperationStart Start the migration.
	OperationStart Operation = "Start"
	// OperationUnhide Unhide the hostpool.
	OperationUnhide Operation = "Unhide"
)

// PossibleOperationValues returns an array of possible values for the Operation const type.
func PossibleOperationValues() []Operation {
	return []Operation{OperationComplete, OperationHide, OperationRevoke, OperationStart, OperationUnhide}
}

// PersonalDesktopAssignmentType enumerates the values for personal desktop assignment type.
type PersonalDesktopAssignmentType string

const (
	// PersonalDesktopAssignmentTypeAutomatic ...
	PersonalDesktopAssignmentTypeAutomatic PersonalDesktopAssignmentType = "Automatic"
	// PersonalDesktopAssignmentTypeDirect ...
	PersonalDesktopAssignmentTypeDirect PersonalDesktopAssignmentType = "Direct"
)

// PossiblePersonalDesktopAssignmentTypeValues returns an array of possible values for the PersonalDesktopAssignmentType const type.
func PossiblePersonalDesktopAssignmentTypeValues() []PersonalDesktopAssignmentType {
	return []PersonalDesktopAssignmentType{PersonalDesktopAssignmentTypeAutomatic, PersonalDesktopAssignmentTypeDirect}
}

// PreferredAppGroupType enumerates the values for preferred app group type.
type PreferredAppGroupType string

const (
	// PreferredAppGroupTypeDesktop ...
	PreferredAppGroupTypeDesktop PreferredAppGroupType = "Desktop"
	// PreferredAppGroupTypeNone ...
	PreferredAppGroupTypeNone PreferredAppGroupType = "None"
	// PreferredAppGroupTypeRailApplications ...
	PreferredAppGroupTypeRailApplications PreferredAppGroupType = "RailApplications"
)

// PossiblePreferredAppGroupTypeValues returns an array of possible values for the PreferredAppGroupType const type.
func PossiblePreferredAppGroupTypeValues() []PreferredAppGroupType {
	return []PreferredAppGroupType{PreferredAppGroupTypeDesktop, PreferredAppGroupTypeNone, PreferredAppGroupTypeRailApplications}
}

// PrivateEndpointConnectionProvisioningState enumerates the values for private endpoint connection
// provisioning state.
type PrivateEndpointConnectionProvisioningState string

const (
	// PrivateEndpointConnectionProvisioningStateCreating ...
	PrivateEndpointConnectionProvisioningStateCreating PrivateEndpointConnectionProvisioningState = "Creating"
	// PrivateEndpointConnectionProvisioningStateDeleting ...
	PrivateEndpointConnectionProvisioningStateDeleting PrivateEndpointConnectionProvisioningState = "Deleting"
	// PrivateEndpointConnectionProvisioningStateFailed ...
	PrivateEndpointConnectionProvisioningStateFailed PrivateEndpointConnectionProvisioningState = "Failed"
	// PrivateEndpointConnectionProvisioningStateSucceeded ...
	PrivateEndpointConnectionProvisioningStateSucceeded PrivateEndpointConnectionProvisioningState = "Succeeded"
)

// PossiblePrivateEndpointConnectionProvisioningStateValues returns an array of possible values for the PrivateEndpointConnectionProvisioningState const type.
func PossiblePrivateEndpointConnectionProvisioningStateValues() []PrivateEndpointConnectionProvisioningState {
	return []PrivateEndpointConnectionProvisioningState{PrivateEndpointConnectionProvisioningStateCreating, PrivateEndpointConnectionProvisioningStateDeleting, PrivateEndpointConnectionProvisioningStateFailed, PrivateEndpointConnectionProvisioningStateSucceeded}
}

// PrivateEndpointServiceConnectionStatus enumerates the values for private endpoint service connection status.
type PrivateEndpointServiceConnectionStatus string

const (
	// PrivateEndpointServiceConnectionStatusApproved ...
	PrivateEndpointServiceConnectionStatusApproved PrivateEndpointServiceConnectionStatus = "Approved"
	// PrivateEndpointServiceConnectionStatusPending ...
	PrivateEndpointServiceConnectionStatusPending PrivateEndpointServiceConnectionStatus = "Pending"
	// PrivateEndpointServiceConnectionStatusRejected ...
	PrivateEndpointServiceConnectionStatusRejected PrivateEndpointServiceConnectionStatus = "Rejected"
)

// PossiblePrivateEndpointServiceConnectionStatusValues returns an array of possible values for the PrivateEndpointServiceConnectionStatus const type.
func PossiblePrivateEndpointServiceConnectionStatusValues() []PrivateEndpointServiceConnectionStatus {
	return []PrivateEndpointServiceConnectionStatus{PrivateEndpointServiceConnectionStatusApproved, PrivateEndpointServiceConnectionStatusPending, PrivateEndpointServiceConnectionStatusRejected}
}

// PublicNetworkAccess enumerates the values for public network access.
type PublicNetworkAccess string

const (
	// PublicNetworkAccessDisabled ...
	PublicNetworkAccessDisabled PublicNetworkAccess = "Disabled"
	// PublicNetworkAccessEnabled ...
	PublicNetworkAccessEnabled PublicNetworkAccess = "Enabled"
)

// PossiblePublicNetworkAccessValues returns an array of possible values for the PublicNetworkAccess const type.
func PossiblePublicNetworkAccessValues() []PublicNetworkAccess {
	return []PublicNetworkAccess{PublicNetworkAccessDisabled, PublicNetworkAccessEnabled}
}

// RegistrationTokenOperation enumerates the values for registration token operation.
type RegistrationTokenOperation string

const (
	// RegistrationTokenOperationDelete ...
	RegistrationTokenOperationDelete RegistrationTokenOperation = "Delete"
	// RegistrationTokenOperationNone ...
	RegistrationTokenOperationNone RegistrationTokenOperation = "None"
	// RegistrationTokenOperationUpdate ...
	RegistrationTokenOperationUpdate RegistrationTokenOperation = "Update"
)

// PossibleRegistrationTokenOperationValues returns an array of possible values for the RegistrationTokenOperation const type.
func PossibleRegistrationTokenOperationValues() []RegistrationTokenOperation {
	return []RegistrationTokenOperation{RegistrationTokenOperationDelete, RegistrationTokenOperationNone, RegistrationTokenOperationUpdate}
}

// RemoteApplicationType enumerates the values for remote application type.
type RemoteApplicationType string

const (
	// RemoteApplicationTypeInBuilt ...
	RemoteApplicationTypeInBuilt RemoteApplicationType = "InBuilt"
	// RemoteApplicationTypeMsixApplication ...
	RemoteApplicationTypeMsixApplication RemoteApplicationType = "MsixApplication"
)

// PossibleRemoteApplicationTypeValues returns an array of possible values for the RemoteApplicationType const type.
func PossibleRemoteApplicationTypeValues() []RemoteApplicationType {
	return []RemoteApplicationType{RemoteApplicationTypeInBuilt, RemoteApplicationTypeMsixApplication}
}

// ResourceIdentityType enumerates the values for resource identity type.
type ResourceIdentityType string

const (
	// ResourceIdentityTypeSystemAssigned ...
	ResourceIdentityTypeSystemAssigned ResourceIdentityType = "SystemAssigned"
)

// PossibleResourceIdentityTypeValues returns an array of possible values for the ResourceIdentityType const type.
func PossibleResourceIdentityTypeValues() []ResourceIdentityType {
	return []ResourceIdentityType{ResourceIdentityTypeSystemAssigned}
}

// ScalingHostPoolType enumerates the values for scaling host pool type.
type ScalingHostPoolType string

const (
	// ScalingHostPoolTypePooled Users get a new (random) SessionHost every time it connects to the HostPool.
	ScalingHostPoolTypePooled ScalingHostPoolType = "Pooled"
)

// PossibleScalingHostPoolTypeValues returns an array of possible values for the ScalingHostPoolType const type.
func PossibleScalingHostPoolTypeValues() []ScalingHostPoolType {
	return []ScalingHostPoolType{ScalingHostPoolTypePooled}
}

// SessionHostLoadBalancingAlgorithm enumerates the values for session host load balancing algorithm.
type SessionHostLoadBalancingAlgorithm string

const (
	// SessionHostLoadBalancingAlgorithmBreadthFirst ...
	SessionHostLoadBalancingAlgorithmBreadthFirst SessionHostLoadBalancingAlgorithm = "BreadthFirst"
	// SessionHostLoadBalancingAlgorithmDepthFirst ...
	SessionHostLoadBalancingAlgorithmDepthFirst SessionHostLoadBalancingAlgorithm = "DepthFirst"
)

// PossibleSessionHostLoadBalancingAlgorithmValues returns an array of possible values for the SessionHostLoadBalancingAlgorithm const type.
func PossibleSessionHostLoadBalancingAlgorithmValues() []SessionHostLoadBalancingAlgorithm {
	return []SessionHostLoadBalancingAlgorithm{SessionHostLoadBalancingAlgorithmBreadthFirst, SessionHostLoadBalancingAlgorithmDepthFirst}
}

// SessionState enumerates the values for session state.
type SessionState string

const (
	// SessionStateActive ...
	SessionStateActive SessionState = "Active"
	// SessionStateDisconnected ...
	SessionStateDisconnected SessionState = "Disconnected"
	// SessionStateLogOff ...
	SessionStateLogOff SessionState = "LogOff"
	// SessionStatePending ...
	SessionStatePending SessionState = "Pending"
	// SessionStateUnknown ...
	SessionStateUnknown SessionState = "Unknown"
	// SessionStateUserProfileDiskMounted ...
	SessionStateUserProfileDiskMounted SessionState = "UserProfileDiskMounted"
)

// PossibleSessionStateValues returns an array of possible values for the SessionState const type.
func PossibleSessionStateValues() []SessionState {
	return []SessionState{SessionStateActive, SessionStateDisconnected, SessionStateLogOff, SessionStatePending, SessionStateUnknown, SessionStateUserProfileDiskMounted}
}

// SkuTier enumerates the values for sku tier.
type SkuTier string

const (
	// SkuTierBasic ...
	SkuTierBasic SkuTier = "Basic"
	// SkuTierFree ...
	SkuTierFree SkuTier = "Free"
	// SkuTierPremium ...
	SkuTierPremium SkuTier = "Premium"
	// SkuTierStandard ...
	SkuTierStandard SkuTier = "Standard"
)

// PossibleSkuTierValues returns an array of possible values for the SkuTier const type.
func PossibleSkuTierValues() []SkuTier {
	return []SkuTier{SkuTierBasic, SkuTierFree, SkuTierPremium, SkuTierStandard}
}

// SSOSecretType enumerates the values for sso secret type.
type SSOSecretType string

const (
	// SSOSecretTypeCertificate ...
	SSOSecretTypeCertificate SSOSecretType = "Certificate"
	// SSOSecretTypeCertificateInKeyVault ...
	SSOSecretTypeCertificateInKeyVault SSOSecretType = "CertificateInKeyVault"
	// SSOSecretTypeSharedKey ...
	SSOSecretTypeSharedKey SSOSecretType = "SharedKey"
	// SSOSecretTypeSharedKeyInKeyVault ...
	SSOSecretTypeSharedKeyInKeyVault SSOSecretType = "SharedKeyInKeyVault"
)

// PossibleSSOSecretTypeValues returns an array of possible values for the SSOSecretType const type.
func PossibleSSOSecretTypeValues() []SSOSecretType {
	return []SSOSecretType{SSOSecretTypeCertificate, SSOSecretTypeCertificateInKeyVault, SSOSecretTypeSharedKey, SSOSecretTypeSharedKeyInKeyVault}
}

// Status enumerates the values for status.
type Status string

const (
	// StatusAvailable Session Host has passed all the health checks and is available to handle connections.
	StatusAvailable Status = "Available"
	// StatusDisconnected The Session Host is unavailable because it is currently disconnected.
	StatusDisconnected Status = "Disconnected"
	// StatusDomainTrustRelationshipLost SessionHost's domain trust relationship lost
	StatusDomainTrustRelationshipLost Status = "DomainTrustRelationshipLost"
	// StatusFSLogixNotHealthy FSLogix is in an unhealthy state on the session host.
	StatusFSLogixNotHealthy Status = "FSLogixNotHealthy"
	// StatusNeedsAssistance New status to inform admins that the health on their endpoint needs to be fixed.
	// The connections might not fail, as these issues are not fatal.
	StatusNeedsAssistance Status = "NeedsAssistance"
	// StatusNoHeartbeat The Session Host is not heart beating.
	StatusNoHeartbeat Status = "NoHeartbeat"
	// StatusNotJoinedToDomain SessionHost is not joined to domain.
	StatusNotJoinedToDomain Status = "NotJoinedToDomain"
	// StatusShutdown Session Host is shutdown - RD Agent reported session host to be stopped or deallocated.
	StatusShutdown Status = "Shutdown"
	// StatusSxSStackListenerNotReady SxS stack installed on the SessionHost is not ready to receive
	// connections.
	StatusSxSStackListenerNotReady Status = "SxSStackListenerNotReady"
	// StatusUnavailable Session Host is either turned off or has failed critical health checks which is
	// causing service not to be able to route connections to this session host. Note this replaces previous
	// 'NoHeartBeat' status.
	StatusUnavailable Status = "Unavailable"
	// StatusUpgradeFailed Session Host is unavailable because the critical component upgrade (agent,
	// side-by-side stack, etc.) failed.
	StatusUpgradeFailed Status = "UpgradeFailed"
	// StatusUpgrading Session Host is unavailable because currently an upgrade of RDAgent/side-by-side stack
	// is in progress. Note: this state will be removed once the upgrade completes and the host is able to
	// accept connections.
	StatusUpgrading Status = "Upgrading"
)

// PossibleStatusValues returns an array of possible values for the Status const type.
func PossibleStatusValues() []Status {
	return []Status{StatusAvailable, StatusDisconnected, StatusDomainTrustRelationshipLost, StatusFSLogixNotHealthy, StatusNeedsAssistance, StatusNoHeartbeat, StatusNotJoinedToDomain, StatusShutdown, StatusSxSStackListenerNotReady, StatusUnavailable, StatusUpgradeFailed, StatusUpgrading}
}

// StopHostsWhen enumerates the values for stop hosts when.
type StopHostsWhen string

const (
	// StopHostsWhenZeroActiveSessions ...
	StopHostsWhenZeroActiveSessions StopHostsWhen = "ZeroActiveSessions"
	// StopHostsWhenZeroSessions ...
	StopHostsWhenZeroSessions StopHostsWhen = "ZeroSessions"
)

// PossibleStopHostsWhenValues returns an array of possible values for the StopHostsWhen const type.
func PossibleStopHostsWhenValues() []StopHostsWhen {
	return []StopHostsWhen{StopHostsWhenZeroActiveSessions, StopHostsWhenZeroSessions}
}

// UpdateState enumerates the values for update state.
type UpdateState string

const (
	// UpdateStateFailed ...
	UpdateStateFailed UpdateState = "Failed"
	// UpdateStateInitial ...
	UpdateStateInitial UpdateState = "Initial"
	// UpdateStatePending ...
	UpdateStatePending UpdateState = "Pending"
	// UpdateStateStarted ...
	UpdateStateStarted UpdateState = "Started"
	// UpdateStateSucceeded ...
	UpdateStateSucceeded UpdateState = "Succeeded"
)

// PossibleUpdateStateValues returns an array of possible values for the UpdateState const type.
func PossibleUpdateStateValues() []UpdateState {
	return []UpdateState{UpdateStateFailed, UpdateStateInitial, UpdateStatePending, UpdateStateStarted, UpdateStateSucceeded}
}
