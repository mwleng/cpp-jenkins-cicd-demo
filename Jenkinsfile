pipeline {
    agent none
    options {
        timestamps()
        skipDefaultCheckout(true)
    }
    stages {
        stage('Build and test') {
            matrix {
                axes {
                    axis {
                        name 'COMPILER'
                        values 'gcc', 'clang'
                    }
                }
                agent { label 'ubuntu' }
                stages {
                    stage('Checkout') {
                        steps { checkout scm }
                    }
                    stage('Configure') {
                        steps { sh "./scripts/configure.sh build-${COMPILER} ${COMPILER}" }
                    }
                    stage('Compile') {
                        steps { sh "cmake --build build-${COMPILER} --parallel" }
                    }
                    stage('Test') {
                        steps { sh "ctest --test-dir build-${COMPILER} --output-on-failure" }
                    }
                }
            }
        }
        stage('Package') {
            agent { label 'ubuntu' }
            steps {
                checkout scm
                sh './scripts/package.sh'
                archiveArtifacts artifacts: 'dist/*', fingerprint: true
            }
        }
        stage('Publish GitHub release') {
            agent {
                label 'ubuntu'
            }
            when {
                tag pattern: 'v*', comparator: 'GLOB'
            }
            steps {
                script {
                    def releaseTag = env.TAG_NAME ?: env.BRANCH_NAME

                    if (!releaseTag?.startsWith('v')) {
                        error("Release requires a v* tag build; TAG_NAME=${env.TAG_NAME}, BRANCH_NAME=${env.BRANCH_NAME}")
                    }

                    withCredentials([
                        string(
                            credentialsId: 'github-release-token-secret',
                            variable: 'GH_TOKEN'
                        )
                    ]) {
                        withEnv(["RELEASE_TAG=${releaseTag}"]) {
                            sh '''
                                set -eu
                                gh release create "$RELEASE_TAG" dist/* \
                                    --repo mwleng/cpp-jenkins-cicd-demo \
                                    --verify-tag \
                                    --generate-notes
                            '''
                        }
                    }
                }
            }
        }      
    }
}

