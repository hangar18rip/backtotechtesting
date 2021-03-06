package apimanagement

// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See License.txt in the project root for license information.
//
// Code generated by Microsoft (R) AutoRest Code Generator.
// Changes may cause incorrect behavior and will be lost if the code is regenerated.

import (
	"context"
	"github.com/Azure/go-autorest/autorest"
	"github.com/Azure/go-autorest/autorest/azure"
	"github.com/Azure/go-autorest/autorest/validation"
	"github.com/Azure/go-autorest/tracing"
	"net/http"
)

// UserConfirmationPasswordClient is the apiManagement Client
type UserConfirmationPasswordClient struct {
	BaseClient
}

// NewUserConfirmationPasswordClient creates an instance of the UserConfirmationPasswordClient client.
func NewUserConfirmationPasswordClient(subscriptionID string) UserConfirmationPasswordClient {
	return NewUserConfirmationPasswordClientWithBaseURI(DefaultBaseURI, subscriptionID)
}

// NewUserConfirmationPasswordClientWithBaseURI creates an instance of the UserConfirmationPasswordClient client using
// a custom endpoint.  Use this when interacting with an Azure cloud that uses a non-standard base URI (sovereign
// clouds, Azure stack).
func NewUserConfirmationPasswordClientWithBaseURI(baseURI string, subscriptionID string) UserConfirmationPasswordClient {
	return UserConfirmationPasswordClient{NewWithBaseURI(baseURI, subscriptionID)}
}

// SendMethod sends confirmation
// Parameters:
// resourceGroupName - the name of the resource group.
// serviceName - the name of the API Management service.
// userID - user identifier. Must be unique in the current API Management service instance.
// appType - determines the type of application which send the create user request. Default is legacy publisher
// portal.
func (client UserConfirmationPasswordClient) SendMethod(ctx context.Context, resourceGroupName string, serviceName string, userID string, appType AppType) (result autorest.Response, err error) {
	if tracing.IsEnabled() {
		ctx = tracing.StartSpan(ctx, fqdn+"/UserConfirmationPasswordClient.SendMethod")
		defer func() {
			sc := -1
			if result.Response != nil {
				sc = result.Response.StatusCode
			}
			tracing.EndSpan(ctx, sc, err)
		}()
	}
	if err := validation.Validate([]validation.Validation{
		{TargetValue: serviceName,
			Constraints: []validation.Constraint{{Target: "serviceName", Name: validation.MaxLength, Rule: 50, Chain: nil},
				{Target: "serviceName", Name: validation.MinLength, Rule: 1, Chain: nil},
				{Target: "serviceName", Name: validation.Pattern, Rule: `^[a-zA-Z](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?$`, Chain: nil}}},
		{TargetValue: userID,
			Constraints: []validation.Constraint{{Target: "userID", Name: validation.MaxLength, Rule: 80, Chain: nil},
				{Target: "userID", Name: validation.MinLength, Rule: 1, Chain: nil}}}}); err != nil {
		return result, validation.NewError("apimanagement.UserConfirmationPasswordClient", "SendMethod", err.Error())
	}

	req, err := client.SendMethodPreparer(ctx, resourceGroupName, serviceName, userID, appType)
	if err != nil {
		err = autorest.NewErrorWithError(err, "apimanagement.UserConfirmationPasswordClient", "SendMethod", nil, "Failure preparing request")
		return
	}

	resp, err := client.SendMethodSender(req)
	if err != nil {
		result.Response = resp
		err = autorest.NewErrorWithError(err, "apimanagement.UserConfirmationPasswordClient", "SendMethod", resp, "Failure sending request")
		return
	}

	result, err = client.SendMethodResponder(resp)
	if err != nil {
		err = autorest.NewErrorWithError(err, "apimanagement.UserConfirmationPasswordClient", "SendMethod", resp, "Failure responding to request")
		return
	}

	return
}

// SendMethodPreparer prepares the SendMethod request.
func (client UserConfirmationPasswordClient) SendMethodPreparer(ctx context.Context, resourceGroupName string, serviceName string, userID string, appType AppType) (*http.Request, error) {
	pathParameters := map[string]interface{}{
		"resourceGroupName": autorest.Encode("path", resourceGroupName),
		"serviceName":       autorest.Encode("path", serviceName),
		"subscriptionId":    autorest.Encode("path", client.SubscriptionID),
		"userId":            autorest.Encode("path", userID),
	}

	const APIVersion = "2021-08-01"
	queryParameters := map[string]interface{}{
		"api-version": APIVersion,
	}
	if len(string(appType)) > 0 {
		queryParameters["appType"] = autorest.Encode("query", appType)
	} else {
		queryParameters["appType"] = autorest.Encode("query", "portal")
	}

	preparer := autorest.CreatePreparer(
		autorest.AsPost(),
		autorest.WithBaseURL(client.BaseURI),
		autorest.WithPathParameters("/subscriptions/{subscriptionId}/resourceGroups/{resourceGroupName}/providers/Microsoft.ApiManagement/service/{serviceName}/users/{userId}/confirmations/password/send", pathParameters),
		autorest.WithQueryParameters(queryParameters))
	return preparer.Prepare((&http.Request{}).WithContext(ctx))
}

// SendMethodSender sends the SendMethod request. The method will close the
// http.Response Body if it receives an error.
func (client UserConfirmationPasswordClient) SendMethodSender(req *http.Request) (*http.Response, error) {
	return client.Send(req, azure.DoRetryWithRegistration(client.Client))
}

// SendMethodResponder handles the response to the SendMethod request. The method always
// closes the http.Response Body.
func (client UserConfirmationPasswordClient) SendMethodResponder(resp *http.Response) (result autorest.Response, err error) {
	err = autorest.Respond(
		resp,
		azure.WithErrorUnlessStatusCode(http.StatusOK, http.StatusNoContent),
		autorest.ByClosing())
	result.Response = resp
	return
}
