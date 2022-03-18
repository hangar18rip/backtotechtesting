package recoveryservices

// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See License.txt in the project root for license information.
//
// Code generated by Microsoft (R) AutoRest Code Generator.
// Changes may cause incorrect behavior and will be lost if the code is regenerated.

import (
	"context"
	"github.com/Azure/go-autorest/autorest"
	"github.com/Azure/go-autorest/autorest/azure"
	"github.com/Azure/go-autorest/tracing"
	"net/http"
)

// VaultCertificatesClient is the recovery Services Client
type VaultCertificatesClient struct {
	BaseClient
}

// NewVaultCertificatesClient creates an instance of the VaultCertificatesClient client.
func NewVaultCertificatesClient(subscriptionID string) VaultCertificatesClient {
	return NewVaultCertificatesClientWithBaseURI(DefaultBaseURI, subscriptionID)
}

// NewVaultCertificatesClientWithBaseURI creates an instance of the VaultCertificatesClient client using a custom
// endpoint.  Use this when interacting with an Azure cloud that uses a non-standard base URI (sovereign clouds, Azure
// stack).
func NewVaultCertificatesClientWithBaseURI(baseURI string, subscriptionID string) VaultCertificatesClient {
	return VaultCertificatesClient{NewWithBaseURI(baseURI, subscriptionID)}
}

// Create uploads a certificate for a resource.
// Parameters:
// resourceGroupName - the name of the resource group where the recovery services vault is present.
// vaultName - the name of the recovery services vault.
// certificateName - certificate friendly name.
// certificateRequest - input parameters for uploading the vault certificate.
func (client VaultCertificatesClient) Create(ctx context.Context, resourceGroupName string, vaultName string, certificateName string, certificateRequest CertificateRequest) (result VaultCertificateResponse, err error) {
	if tracing.IsEnabled() {
		ctx = tracing.StartSpan(ctx, fqdn+"/VaultCertificatesClient.Create")
		defer func() {
			sc := -1
			if result.Response.Response != nil {
				sc = result.Response.Response.StatusCode
			}
			tracing.EndSpan(ctx, sc, err)
		}()
	}
	req, err := client.CreatePreparer(ctx, resourceGroupName, vaultName, certificateName, certificateRequest)
	if err != nil {
		err = autorest.NewErrorWithError(err, "recoveryservices.VaultCertificatesClient", "Create", nil, "Failure preparing request")
		return
	}

	resp, err := client.CreateSender(req)
	if err != nil {
		result.Response = autorest.Response{Response: resp}
		err = autorest.NewErrorWithError(err, "recoveryservices.VaultCertificatesClient", "Create", resp, "Failure sending request")
		return
	}

	result, err = client.CreateResponder(resp)
	if err != nil {
		err = autorest.NewErrorWithError(err, "recoveryservices.VaultCertificatesClient", "Create", resp, "Failure responding to request")
		return
	}

	return
}

// CreatePreparer prepares the Create request.
func (client VaultCertificatesClient) CreatePreparer(ctx context.Context, resourceGroupName string, vaultName string, certificateName string, certificateRequest CertificateRequest) (*http.Request, error) {
	pathParameters := map[string]interface{}{
		"certificateName":   autorest.Encode("path", certificateName),
		"resourceGroupName": autorest.Encode("path", resourceGroupName),
		"subscriptionId":    autorest.Encode("path", client.SubscriptionID),
		"vaultName":         autorest.Encode("path", vaultName),
	}

	const APIVersion = "2021-08-01"
	queryParameters := map[string]interface{}{
		"api-version": APIVersion,
	}

	preparer := autorest.CreatePreparer(
		autorest.AsContentType("application/json; charset=utf-8"),
		autorest.AsPut(),
		autorest.WithBaseURL(client.BaseURI),
		autorest.WithPathParameters("/Subscriptions/{subscriptionId}/resourceGroups/{resourceGroupName}/providers/Microsoft.RecoveryServices/vaults/{vaultName}/certificates/{certificateName}", pathParameters),
		autorest.WithJSON(certificateRequest),
		autorest.WithQueryParameters(queryParameters))
	return preparer.Prepare((&http.Request{}).WithContext(ctx))
}

// CreateSender sends the Create request. The method will close the
// http.Response Body if it receives an error.
func (client VaultCertificatesClient) CreateSender(req *http.Request) (*http.Response, error) {
	return client.Send(req, azure.DoRetryWithRegistration(client.Client))
}

// CreateResponder handles the response to the Create request. The method always
// closes the http.Response Body.
func (client VaultCertificatesClient) CreateResponder(resp *http.Response) (result VaultCertificateResponse, err error) {
	err = autorest.Respond(
		resp,
		azure.WithErrorUnlessStatusCode(http.StatusOK),
		autorest.ByUnmarshallingJSON(&result),
		autorest.ByClosing())
	result.Response = autorest.Response{Response: resp}
	return
}
