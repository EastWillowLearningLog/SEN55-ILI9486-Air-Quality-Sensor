# Update Github Actions to V4

## Problem Statement
The current Github Actions workflows use mixed versions of standard actions. specifically `actions/checkout` and `actions/upload-artifact` are using v3 in `integration-test.yml`, while other workflows have been updated to v4. This inconsistency can lead to maintenance issues and missing features/fixes available in v4.

## Proposed Solution
Update `integration-test.yml` to use `actions/checkout@v4` and `actions/upload-artifact@v4` to match the rest of the project workflows and follow the new standard.

## Impact
- Consistency across all CI workflows.
- Access to latest features and fixes from v4 actions.
