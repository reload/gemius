<?php

/**
 * Implementation of hook_admin_settings() for configuring the module
 */
function gemius_admin_settings_form(&$form_state) {
  $form['account'] = array(
    '#type' => 'fieldset',
    '#title' => t('General settings'),
    '#collapsible' => FALSE,
  );

  $form['account']['gemius_key'] = array(
    '#type' => 'textfield',
    '#title' => t('Gemius identifier'),
    '#default_value' => variable_get('gemius_key', ''),
    '#size' => 30,
    '#maxlength' => 30,
    '#required' => TRUE,
    '#description' => t('The identifier'),
  );

  // Page specific visibility configurations.
  $form['page_vis_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Page specific tracking settings'),
    '#collapsible' => false,
    /*'#collapsed' => TRUE,*/
  );

  $pages = variable_get('gemius_pages', '');
  $description = t("Enter one page per line as Drupal paths. The '*' character is a wildcard. Example paths are %blog for the blog page and %blog-wildcard for every personal blog. %front is the front page.", array('%blog' => 'blog', '%blog-wildcard' => 'blog/*', '%front' => '<front>'));
  
  $form['page_vis_settings']['gemius_pages'] = array(
    '#type' => 'textarea',
    '#title' => t('Pages to be excluded from statistics'),
    '#default_value' => $pages,
    '#description' => $description,
    '#wysiwyg' => FALSE,
  );
  
    // Render the role overview.
  $form['role_vis_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Role specific tracking settings'),
    '#collapsible' => false,
  );

  $roles = user_roles();
  $role_options = array();
  foreach ($roles as $rid => $name) {
    $role_options[$rid] = $name;
  }
  $form['role_vis_settings']['gemius_roles'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Add tracking for specific roles'),
    '#default_value' => variable_get('gemius_roles', array()),
    '#options' => $role_options,
    '#description' => t('Add tracking only for the selected role(s). If none of the roles are selected, all users will be tracked. If a user has any of the roles checked, that user will be tracked.'),
  );
  

  return system_settings_form($form);
}
/*
function googleanalytics_admin_settings_form_validate($form, &$form_state) {
  if (!preg_match('/^UA-\d{4,}-\d+$/', $form_state['values']['googleanalytics_account'])) {
    form_set_error('googleanalytics_account', t('A valid Google Analytics account number is case sensitive and formatted like UA-xxxxxx-x.'));
  }

  // This is for the Newbie's who cannot read a text area description.
  if (stristr($form_state['values']['googleanalytics_codesnippet_before'], 'google-analytics.com/ga.js')) {
    form_set_error('googleanalytics_codesnippet_before', t('Do not add the tracker code provided by Google into the javascript code snippets! This module already builds the tracker code based on your Google Analytics account number and settings.'));
  }
  if (stristr($form_state['values']['googleanalytics_codesnippet_after'], 'google-analytics.com/ga.js')) {
    form_set_error('googleanalytics_codesnippet_after', t('Do not add the tracker code provided by Google into the javascript code snippets! This module already builds the tracker code based on your Google Analytics account number and settings.'));
  }
  if (preg_match('/(.*)<\/?script(.*)>(.*)/i', $form_state['values']['googleanalytics_codesnippet_before'])) {
    form_set_error('googleanalytics_codesnippet_before', t('Do not include the &lt;script&gt; tags in the javascript code snippets.'));
  }
  if (preg_match('/(.*)<\/?script(.*)>(.*)/i', $form_state['values']['googleanalytics_codesnippet_after'])) {
    form_set_error('googleanalytics_codesnippet_after', t('Do not include the &lt;script&gt; tags in the javascript code snippets.'));
  }

  // Trim some text area values.
  $form_state['values']['googleanalytics_pages'] = trim($form_state['values']['googleanalytics_pages']);
  $form_state['values']['googleanalytics_codesnippet_before'] = trim($form_state['values']['googleanalytics_codesnippet_before']);
  $form_state['values']['googleanalytics_codesnippet_after'] = trim($form_state['values']['googleanalytics_codesnippet_after']);
}
  */