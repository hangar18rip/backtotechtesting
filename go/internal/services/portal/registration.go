package portal

import (
	"github.com/hashicorp/terraform-provider-azurerm/internal/features"
	"github.com/hashicorp/terraform-provider-azurerm/internal/sdk"
	"github.com/hashicorp/terraform-provider-azurerm/internal/tf/pluginsdk"
)

type Registration struct{}

var _ sdk.UntypedServiceRegistrationWithAGitHubLabel = Registration{}

func (r Registration) AssociatedGitHubLabel() string {
	return "service/portal"
}

// Name is the name of this Service
func (r Registration) Name() string {
	return "Portal"
}

// WebsiteCategories returns a list of categories which can be used for the sidebar
func (r Registration) WebsiteCategories() []string {
	return []string{
		"Portal",
	}
}

// SupportedDataSources returns the supported Data Sources supported by this Service
func (r Registration) SupportedDataSources() map[string]*pluginsdk.Resource {
	return map[string]*pluginsdk.Resource{
		"azurerm_portal_dashboard": dataSourcePortalDashboard(),
	}
}

// SupportedResources returns the supported Resources supported by this Service
func (r Registration) SupportedResources() map[string]*pluginsdk.Resource {
	dashboardName := "azurerm_portal_dashboard"
	if !features.ThreePointOhBeta() {
		dashboardName = "azurerm_dashboard"
	}
	return map[string]*pluginsdk.Resource{
		dashboardName:                         resourceDashboard(),
		"azurerm_portal_tenant_configuration": resourcePortalTenantConfiguration(),
	}
}
